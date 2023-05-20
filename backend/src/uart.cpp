#include <fstream>
#include <algorithm>
#include <cmath>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_wavelet.h>

#include "uart.h"



void Sensor::acquire()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(run_mtx);
        cv.wait(lock,[this]{return run;});

        static uint8_t sum;
        static std::string num_str;
        int byte;
        sp_blocking_read(port,&byte,1,100);

        // Logger::getInstance().infoStream() << byte;
        switch (state)
        {
        case Sensor_State::HEADER:
            if(byte == 0x23)
            {
                // Logger::getInstance().info("接收到帧头数据");
                sum = 0x23;
                state = Sensor_State::ECG_DATA;
                break;
            }
            break;
        case Sensor_State::ECG_DATA:
            if(byte != 0x0D && (byte >= 0x30 && byte <= 0x39))
            {
                // Logger::getInstance().infoStream() << "接收到ECG数据" << byte;
                sum += byte;
                
                num_str.push_back(static_cast<char>(byte));
                break;
            }
            else
            {
                // Logger::getInstance().info("接收到中间帧数据");
                sum += 0x0D;
                // Logger::getInstance().infoStream() << "ECG数据是" << std::stoi(num_str);
                
                try {
                    ecg_buffer.put(std::stoi(num_str));
                } catch (std::invalid_argument& e) {
                    Logger::getInstance().errorStream() << "参数异常： " << e.what();
                } catch (std::exception& e) {
                    // 处理其他可能的异常
                    Logger::getInstance().errorStream() << "其他错误发生； " << e.what();
                }
                num_str.clear();
                state = Sensor_State::PPG_DATA;
                break;
            }
        // case Sensor_State::INTERVAL:
            
        case Sensor_State::PPG_DATA:
            if(byte >= 0x30 && byte <= 0x39)
            {
                sum += byte;
                // ppg_buffer.put(byte);
                num_str.push_back(static_cast<char>(byte));
                // Logger::getInstance().infoStream() << "接收到PPG数据" << byte;
                break;

                
            }
            else
            {
                Logger::getInstance().infoStream() << "接收到校验和" << static_cast<int>(sum);
                Logger::getInstance().infoStream() << "PPG数据是" << std::stoi(num_str);
                
                try {
                    ppg_buffer.put(std::stoi(num_str));
                } catch (std::invalid_argument& e) {
                    Logger::getInstance().errorStream() << "参数异常： " << e.what();
                } catch (std::exception& e) {
                    // 处理其他可能的异常
                    Logger::getInstance().errorStream() << "其他错误发生； " << e.what();
                }
                num_str.clear();
                state = Sensor_State::TAIL;
                break;
            }
           
        // case Sensor_State::CHECKSUM:
            
        //     break;
        case Sensor_State::TAIL:
            if(byte == 0x0A)
            {
                // Logger::getInstance().info("接收到帧尾");
                state = Sensor_State::HEADER;
                if(ppg_buffer.full() && ecg_buffer.full())
                {
                    std::lock_guard<std::mutex> lock(proc_mtx);
                    ready = true;
                    Logger::getInstance().info("两个缓冲区都满了，可以进行下一步处理");
                }
                cv.notify_all();
                break;
            }
            break;
        default:
            state = Sensor_State::HEADER;
        }
    }
    
}

void Sensor::process()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(proc_mtx);
        cv.wait(lock,[this]{return ready;});

        static double ecg_factor = (1000 * 1.2 * 3.77) / std::pow(2,24);
        static double ppg_factor = 1.024 / std::pow(2,24);

        static size_t p[1024];
        static double abscoeff[1024];
        static gsl_wavelet *w = gsl_wavelet_alloc(gsl_wavelet_daubechies, 8);
        static gsl_wavelet_workspace *work = gsl_wavelet_workspace_alloc(1024);

        Logger::getInstance().info("处理线程开始工作");

        std::vector<int> ecg_vec_int = ecg_buffer.copy_all();
        std::vector<int> ppg_vec_int = ppg_buffer.copy_all();

        for(int i = 0;i < 1024;i++)
        {
            double d_val = static_cast<double>(ecg_vec_int[i]);
            d_val = (d_val * 2.3 * ecg_factor) / 60;
            ecg_processed[i] = d_val;
        }

        for(int i = 0;i < 1024;i++)
        {
            double d_val = static_cast<double>(ppg_vec_int[i]);
            d_val = (d_val * 2.3 * ecg_factor) / 60;
            ppg_processed[i] = d_val;
        }

        std::ofstream original_file("original.txt", std::ios::out);
        std::ofstream transformed_file("transformed.txt", std::ios::out);
        for(int i =0;i < 1024;i++)
        {
            original_file << ecg_processed[i] << "\n";
        }

        gsl_wavelet_transform_forward(w,ecg_processed,1,1024,work);
        for (int i = 0; i < 1024; i++)
        {
            abscoeff[i] = fabs (ecg_processed[i]);
        }
        gsl_sort_index (p, abscoeff, 1, 1024);

        for (int i = 0; (i + 20) < 1024; i++)
            ecg_processed[p[i]] = 0;

        gsl_wavelet_transform_inverse(w,ecg_processed,1,1024,work);

        for(int i =0;i < 1024;i++)
        {
            transformed_file << ecg_processed[i] << "\n";
        }
        
        original_file.close();
        transformed_file.close();
        ready = false;
    }
}

void Sensor::start()
{
    //先给传感器发送命令，开始采集数据，再启动线程接收数据
    const unsigned char start[] = {0x14, 0x01, 0x15, 0x0D};
    sp_blocking_write(port, start, sizeof(start), 100);

    {
        std::lock_guard<std::mutex> lock(run_mtx);
        run = true; 
    }
    cv.notify_all();


    Logger::getInstance().info("启动串口线程");
}

void Sensor::stop()
{
    const unsigned char stop[] = {0x14, 0x00, 0x14, 0x0D};
    sp_blocking_write(port, stop, sizeof(stop), 100);
    {
        std::lock_guard<std::mutex> lock(run_mtx);
        run = false; 
    }
    cv.notify_all();
    Logger::getInstance().info("关闭串口线程");
}

#ifndef __UART_H__
#define __UART_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "libserialport.h"

#include "log.h"
#include "CircularBuffer.h"


enum class Sensor_State {
    HEADER,
    ECG_DATA,
    //INTERVAL和ECG_DATA放到一起处理
    PPG_DATA,
    //CHECKSUM和PPG_DATA
    TAIL
};


class Sensor
{
private:
    struct sp_port *port;
    std::string portName;
    CircularBuffer ecg_buffer;
    CircularBuffer ppg_buffer;
    double ecg_processed[1024] = {0};
    double ppg_processed[1024] = {0};
    std::mutex run_mtx;
    std::mutex proc_mtx;
    std::condition_variable cv; 
    bool run = false;
    bool ready = false;
    
    Sensor_State state;
public:
    // 构造函数，设置串口名
    Sensor(const std::string &portName) : portName(portName), state(Sensor_State::HEADER),ecg_buffer(1024),ppg_buffer(1024) {}

    // 打开串口
    bool open()
    {
        sp_return result = sp_get_port_by_name(portName.c_str(), &port);
        if (result != SP_OK) {
            Logger::getInstance().error("找不到CH340串口");
            return false;
        }

        result = sp_open(port, SP_MODE_READ_WRITE);
        if (result != SP_OK) {
            Logger::getInstance().error("无法打开串口");
            return false;
        }
        Logger::getInstance().info("打开CH340串口成功");
        sp_set_baudrate(port, 115200);
        sp_set_bits(port, 8);
        sp_set_parity(port, SP_PARITY_NONE);
        sp_set_stopbits(port, 1);
        sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);
        return true;
    }

    // 关闭串口
    void close()
    {
        sp_close(port);
        sp_free_port(port);
    }

    void acquire();
    void process();
    void start();
    void stop();
};

#endif // !__UART_H__
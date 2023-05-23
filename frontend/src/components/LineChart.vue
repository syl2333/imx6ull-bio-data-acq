<template>
    <div ref="chartRef" style="width: 100%; height: 500px"></div>
</template>
  
<script>
import { ref, onMounted, onBeforeUnmount,onUnmounted } from 'vue'
import * as echarts from 'echarts'
import axios from 'axios';
export default {
    name: 'SmoothWaveformChart',
    setup() {
        const chartRef = ref(null)
        let chartInstance = null
        let timer = null

        const resizeHandler = () => {
            chartInstance.resize();
        }

        const getData = async () => {
            const response = await axios.get('http://192.168.123.25:8000/data')
            const data = response.data
            if(data['status'] === 'ok')
            {
                console.log("获取到数据")
                console.log(data.ecg_data[0]);
                const option = {
                    series: [
                        // {
                        //     name: 'ECG数据',
                        //     type: 'line',
                        //     smooth: false,
                        //     data: data.ecg_data,
                        //     areaStyle: {}
                        // },
                        {
                            name: 'PPG数据',
                            type: 'line',
                            smooth: false,
                            data: data.ppg_data,
                            areaStyle: {}
                        }
                    ]
                }
                chartInstance.setOption(option)
            }
            else
            {
                console.log("暂未获取到数据")
            }
        }

        onMounted(() => {
            // 基于准备好的dom，初始化echarts实例
            chartInstance = echarts.init(chartRef.value)

            // 指定图表的配置项和数据
            const option = {
                title: {
                    text: 'PPG波形图'
                },
                tooltip: {
                    trigger: 'axis'
                },
                xAxis: {
                    type: 'category',
                    data: Array.from({ length: 255 }, (_, i) => i + 1)
                },
                yAxis: {
                    type: 'value'
                },
                dataZoom: [
                    {
                        type: 'inside',
                        xAxisIndex: 0,
                        start: 0,
                        end: 100
                    },
                    {
                        type: 'inside',
                        yAxisIndex: 0,
                        start: 0,
                        end: 100
                    },
                    {
                        type: 'slider',
                        start: 0,
                        end: 10,
                        handleIcon: 'M0,0 v9.7h5 v-9.7h-5 Z',
                        handleSize: '80%',
                        handleStyle: {
                            color: '#fff',
                            shadowBlur: 3,
                            shadowColor: 'rgba(0, 0, 0, 0.6)',
                            shadowOffsetX: 2,
                            shadowOffsetY: 2
                        }
                    },
                ],
            }

            // 使用刚指定的配置项和数据显示图表。
            chartInstance.setOption(option)

            timer = setInterval(getData, 100)

            window.addEventListener('resize', resizeHandler)
        })

        onBeforeUnmount(() => {
            if (chartInstance) {
                chartInstance.dispose()
            }
        })
        onUnmounted(() => {
            window.removeEventListener('resize', resizeHandler)
            clearInterval(timer)
        })

        return {
            chartRef
        }
    }
}
</script>
  
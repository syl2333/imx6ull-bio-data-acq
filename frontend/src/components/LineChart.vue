<template>
    <div ref="chartRef" style="width: 100%; height: 500px"></div>
</template>
  
<script>
import { ref, onMounted, onBeforeUnmount,onUnmounted } from 'vue'
import * as echarts from 'echarts'

export default {
    name: 'SmoothWaveformChart',
    setup() {
        const chartRef = ref(null)
        let chartInstance = null

        const resizeHandler = () => {
            chartInstance.resize();
        }

        onMounted(() => {
            // 基于准备好的dom，初始化echarts实例
            chartInstance = echarts.init(chartRef.value)

            // 指定图表的配置项和数据
            const option = {
                title: {
                    text: '平滑波形图'
                },
                tooltip: {
                    trigger: 'axis'
                },
                xAxis: {
                    type: 'category',
                    data: Array.from({ length: 100 }, (_, i) => i + 1)
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
                series: [
                    {
                        name: '正弦函数',
                        type: 'line',
                        smooth: true,
                        data: Array.from({ length: 100 }, (_,i) => Math.sin(2 * Math.PI * (i+1) /100)),
                        areaStyle: {}
                    },
                    {
                        name: '余弦函数',
                        type: 'line',
                        smooth: true,
                        data: Array.from({ length: 100 }, (_,i) => Math.cos(2 * Math.PI * (i+1) /100)),
                        areaStyle: {}
                    },
                    {
                        name: '正切函数',
                        type: 'line',
                        smooth: true,
                        data: Array.from({ length: 100 }, () => Math.random()),
                        areaStyle: {}
                    },
                ]
            }

            // 使用刚指定的配置项和数据显示图表。
            chartInstance.setOption(option)

            window.addEventListener('resize', resizeHandler)
        })

        onBeforeUnmount(() => {
            if (chartInstance) {
                chartInstance.dispose()
            }
        })
        onUnmounted(() => {
            window.removeEventListener('resize', resizeHandler)
        })

        return {
            chartRef
        }
    }
}
</script>
  
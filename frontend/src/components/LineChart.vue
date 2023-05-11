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
                    text: 'Smooth Waveform'
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
                series: [
                    {
                        name: 'Waveform',
                        type: 'line',
                        smooth: true,
                        data: Array.from({ length: 100 }, () => Math.random() * 10),
                        areaStyle: {}
                    }
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
  
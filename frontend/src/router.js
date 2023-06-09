import { createRouter, createWebHistory } from 'vue-router';
import axios from 'axios';
import LoginBox from './components/Login.vue'
import WelcomeDialog from './components/Welcome.vue';
import HomeLanding from './components/Home.vue'
import SmoothWaveformChart from "@/components/LineChart.vue"
import HistoryData from '@/components/HistoryData'
import FeedBack from '@/components/FeedBack.vue'

const login = async (router, username, password) => {
    try {
        // 开发板的IP地址
        const response = await axios.post('http://192.168.123.25:8000/login', {
            username: username,
            password: password
        });
        console.log('发送数据');
        console.log(username,password);
        if (response.status == 200) {
            console.log('登陆成功');
            console.log(response.data["message"]);
            router.push('/Home');
        }
        if (response.status == 401) {
            console.log('登陆失败');
            console.log(response.data["message"]);
        }
    } catch (error) {
        console.error(error);
        // 在这里处理登录失败后的逻辑，例如显示错误消息
        alert('登录失败，请稍后重试。');
    }
};

const routes = [
    {
        path: '/',
        name: 'Login',
        component: LoginBox,
        props: {onLogin: (username,password) => login(router,username,password)}
    },
    {
        path: '/Home',
        name: 'Home',
        component: HomeLanding,
        children: [
            {
                path: '*',
                redirect: '/Home/DashBoard'
            },
            { 
                path: 'DashBoard', 
                component: SmoothWaveformChart
            },
            { 
                path: 'HistoryData', 
                component: HistoryData
            },
            {
                path: 'FeedBack',
                component: FeedBack
            }
        ]
    },
    {
        path: '/Welcome',
        name: 'Welcome',
        component: WelcomeDialog
    }
];

const router = createRouter({
    history: createWebHistory(),
    routes
});
export default router;

<template>
  <img alt="Vue logo" src="./assets/logo.png">
  <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->
  <Login :onLogin="login"/>
</template>


<script>
// import HelloWorld from './components/HelloWorld.vue'
import axios from 'axios';
import Login from './components/Login.vue'
export default {
  name: 'App',
  components: {
    //HelloWorld,
    Login
  },
  methods: {
    async login(username,password)
    {
      try {
        const response = await axios.post('http://127.0.0.1:8000/login',{
          username:username,
          password:password
        });
        console.log('发送数据');
        if(response.status == 200)
        {
          console.log('登陆成功');
        }

      } catch (error) {
          console.error(error);
          // 在这里处理登录失败后的逻辑，例如显示错误消息
          alert('登录失败，请稍后重试。');
      }
    }
  }
}

</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #14bfd6;
  margin-top: 60px;
}
</style>

<template>
  <img alt="Vue logo" src="./assets/logo.png">
  <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->
  <Login/>
</template>


<script>
// import HelloWorld from './components/HelloWorld.vue'
import Login from './components/Login.vue'
export default {
  name: 'App',
  components: {
    //HelloWorld,
    Login
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

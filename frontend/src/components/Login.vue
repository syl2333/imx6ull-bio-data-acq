<template>
  <img alt="Vue logo" src="../assets/logo.png">
  <v-card class="pa-6">
    <v-text-field v-model="username" label="用户名" type="text"></v-text-field>
    <v-text-field v-model="password" label="密码" type="password"></v-text-field>
    <v-btn @click="login" color="primary">登陆</v-btn>
  </v-card>
  <v-icon icon="fas fa-plus" />
  <v-icon icon="mdi:mdi-minus" />
  <v-icon icon="fas fa-home" />
</template>
  
<script>
export default {
  name: 'LoginBox',
  props: {
    onLogin: Function,
  },
  data() {
    return {
      username: '',
      password: '',
    };
  },
  methods: {
    login() {
      this.onLogin(this.username, this.password);
    },
  },
};
</script>
  
<style scoped>
/* 样式可以根据需要进行调整 */
.pa-6 {
  padding: 3rem;
}
</style>
  
<template>
    <v-dialog v-model="dialog" max-width="500px">
      <v-card>
        <v-card-title class="headline">用户你好</v-card-title>
        <v-card-text>
          <p>欢迎使用IMX6ULL心输出量监测系统！</p>
          <p>本系统仍不完善，如有问题请联系我</p>
        </v-card-text>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn color="primary" text @click="closeDialog">关闭</v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>
</template>
  
<script>
export default {
    name: 'WelcomeDialog',
    data: () => ({
        dialog: true,
    }),
    methods: {
        closeDialog() {
            this.dialog = false;
        },
    },
};
</script>
  
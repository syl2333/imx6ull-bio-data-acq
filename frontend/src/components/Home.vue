<template>
  <SlideBar></SlideBar>
  
  <v-mian>
    <v-container>
      <router-view></router-view>
    </v-container>
  </v-mian>
    
  
</template>
  
<script>
import SlideBar from "@/components/layout/SlideBar.vue";
export default {
  components: {
    SlideBar,
  },
  name: 'HomeLanding',
};
</script>

<style scoped>
.chart {
  height: 100vh;
}
</style>
  
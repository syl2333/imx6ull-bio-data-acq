<template>
  <SlideBar ></SlideBar>
  
  <v-mian>
    <v-container>
      
      <router-view></router-view>
    </v-container>
  </v-mian>
    
  
</template>
  
<script>
import {onMounted} from 'vue'
import { useRouter } from 'vue-router'
import SlideBar from "@/components/layout/SlideBar.vue";
export default {
  components: {
    SlideBar,
  },
  name: 'HomeLanding',
  setup() {
    const router = useRouter();

    onMounted(() => {
      router.push('/Home/DashBoard');
    });

    return {}
  }
};
</script>

<style scoped>
.chart {
  height: 100vh;
}
</style>
  
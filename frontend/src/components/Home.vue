<template>
  <v-card >
    <v-layout>
      <SlideBar />

      <v-main style="height: 900px;">
        <v-container >
          <router-view></router-view>
        </v-container>
      </v-main>
    </v-layout>
  </v-card>
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
/* .chart {
  height: 100vh;
} */
</style>
  
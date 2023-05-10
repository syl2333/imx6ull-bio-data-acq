<template>
    <SlideBar></SlideBar>
    <router-view></router-view>
</template>
  
<script>
import SlideBar from "@/components/layout/SlideBar.vue";

export default {
    components: {
        SlideBar
    },
    name: 'HomeLanding'
};
</script>
  
import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import 'vuetify/styles'
import { createVuetify } from 'vuetify'
import * as components from 'vuetify/components'
import * as directives from 'vuetify/directives'
import '@fortawesome/fontawesome-free/css/all.css' 
import '@mdi/font/css/materialdesignicons.css' 
import { aliases, fa } from 'vuetify/iconsets/fa'
import { mdi } from 'vuetify/iconsets/mdi'
// 引入Vuetify组件库
const vuetify = createVuetify({
  components,
  directives,
  icons: {
    defaultSet: 'fa',
    aliases,
    sets: {
      fa,
      mdi,
    },
  },
})


createApp(App).use(vuetify).use(router).mount('#app')
//.use(fontawesome)
// new Vue({
//   vuetify,
//   router,
//   render: h => h(App)
// }).$mount('#app');
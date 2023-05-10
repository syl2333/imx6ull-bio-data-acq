import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import 'vuetify/styles'
import { createVuetify } from 'vuetify'
import * as components from 'vuetify/components'
import * as directives from 'vuetify/directives'
import { fontawesome } from "@fortawesome/fontawesome-free"
import '@fortawesome/fontawesome-free/css/all.css'

// 引入Vuetify组件库
const vuetify = createVuetify({
  components,
  directives,
})


createApp(App).use(vuetify).use(fontawesome).use(router).mount('#app')
// new Vue({
//   vuetify,
//   router,
//   render: h => h(App)
// }).$mount('#app');
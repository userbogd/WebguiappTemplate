<template>
  <q-layout view="Hlr Lpr lFf" class="body">
    <q-header>
      <q-toolbar>
        <q-btn flat dense round icon="menu" aria-label="Menu" @click="toggleLeftDrawer" />
        <q-toolbar-title>{{ data.net_bios_name }} {{ data.dev_id }}</q-toolbar-title>
      </q-toolbar>
    </q-header>
    <q-drawer v-model="leftDrawerOpen" show-if-above>
      <q-list>
        <EssentialLink v-for="link in linksList" :key="link.title" v-bind="link" />
      </q-list>
    </q-drawer>
    <q-page-container>
      <router-view></router-view>
    </q-page-container>
  </q-layout>
</template>

<script setup>
import { ref, reactive, watch } from "vue";
import { PostData } from "src/components/webguicomp/network";
import EssentialLink from "components/webguicomp/EssentialLink.vue";
import { setCssVar, useQuasar } from 'quasar'
const $q = useQuasar();
const linksList = [
  { title: "HOME", caption: "Main page", icon: "home", link: "#/home" },
  { title: "SETTINGS", caption: "Application settings", icon: "apps", link: "#/appset" },
  { title: "NETWORK", caption: "Network settings", icon: "public", link: "#/ifsettings" },
  { title: "SERVICES", caption: "System services", icon: "miscellaneous_services", link: "#/services" },
  { title: "SYSTEM", caption: "System tools", icon: "build", link: "#/system" },
  { title: "STORAGE", caption: "Local storage", icon: "storage", link: "#/storage" }
];

function toggleLeftDrawer() { leftDrawerOpen.value = !leftDrawerOpen.value; }
const leftDrawerOpen = ref(false);

const init = {
  model_name: '',
  dev_id: '',
  net_bios_name: '',
  primary_color: '',
  color_scheme: 1
}
const data = reactive(init);
PostData(data, 2, 0, null);
watch(() => data.primary_color, (color) => { setCssVar('primary', color) })
watch(() => data.color_scheme, (scheme) => {
  switch (scheme) {
    case 1:
      $q.dark.set(fasle);
      break;
    case 2:
      $q.dark.set(true);
      break;
  }
})
</script>

<template>
  <q-layout view="hLr Lpr lFf" class="body">
    <q-header>
      <q-toolbar>
        <q-btn flat dense round icon="menu" aria-label="Menu" @click="toggleLeftDrawer" />
        <q-toolbar-title> ESP32 WEBGUIAPP </q-toolbar-title>
      </q-toolbar>
    </q-header>
    <q-drawer v-model="leftDrawerOpen" show-if-above bordered>
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
import { ref, defineAsyncComponent } from "vue";
import EssentialLink from "components/webguicomp/EssentialLink.vue";

const linksList = [
  { title: "HOME", caption: "Main page", icon: "home", link: "#/home" },
  { title: "APPLICATION", caption: "Application", icon: "apps", link: "#/page2" },
  { title: "NETWORK", caption: "Network settings", icon: "public", link: "#/ifsettings" },
  { title: "SERVICES", caption: "System services", icon: "miscellaneous_services", link: "#/services" },
  { title: "SYSTEM", caption: "System tools", icon: "build", link: "#/system" }
];

function toggleLeftDrawer() { leftDrawerOpen.value = !leftDrawerOpen.value; }
const leftDrawerOpen = ref(false);

</script>

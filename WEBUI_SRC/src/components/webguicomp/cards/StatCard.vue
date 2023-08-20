<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">INFO</div>
    </q-card-section>

    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <div>{{ timestr }}</div>
          <div>Uptime: {{ uptimestr }}</div>
          <div>WiFi signal: {{ data.wifi_level }}</div>
          <q-separator inset />
          <div>Ethernet state: {{ data.eth_stat }}</div>
          <div>WiFi state: {{ data.wifi_stat }}</div>
          <div>GPRS state: {{ data.gsm_stat }}</div>
          <q-separator inset />
          <div>MQTT1 state: {{ data.mqtt_1_stat }}</div>
          <div>MQTT2 state: {{ data.mqtt_2_stat }}</div>
          <q-separator inset />
          <div>Free RAM: {{ data.free_ram }}</div>
          <div>Minimal free RAM: {{ data.free_ram_min }}</div>
        </div>
      </div>
    </q-card-section>


  </q-card>
</template>

<script setup>
import { computed, onUnmounted, reactive, onMounted } from "vue";
import { SendAndRequest } from "boot/network";
import { secondsToHms } from "boot/helpers"

defineOptions({
  name: 'StatCard'
})

const init = {
  time: 0,
  uptime: 0,
  wifi_level: "",
  eth_stat: "",
  wifi_stat: "",
  gsm_stat: "",
  mqtt_1_stat: "",
  mqtt_2_stat: "",
  free_ram: 0,
  free_ram_min: 0
}
const data = reactive(init);
SendAndRequest(data, 2, 0, 'mykey', false);

let intervalId
onMounted(() => {
  intervalId = setInterval(() => {
    SendAndRequest(data, 2, 0, 'mykey', false);
  }, 1000)
})
onUnmounted(() => clearInterval(intervalId))
const timestr = computed({ get() { return (new Date(data.time * 1000).toISOString()) } })
const uptimestr = computed({ get() { return (secondsToHms(data.uptime)) } })

</script>

<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">Home</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <div>{{ timestr }}</div>
          <div>Uptime: {{ uptimestr }}</div>
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
  name: 'HomeCard'
})

const init = {
  time: 0,
  uptime: 0
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

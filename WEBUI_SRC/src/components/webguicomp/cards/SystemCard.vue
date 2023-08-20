<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">SYSTEM</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <q-input :dense="true" v-model="data.net_bios_name" label="Device bios name" />
          <q-input :dense="true" v-model="data.sys_name" label="User name" />
          <q-input :dense="true" v-model="data.sys_pass" label="User password" />
          <div>Device model: {{ data.model_name }}</div>
          <div>Hardware revision: {{ data.hw_rev }}</div>
          <div>Firmware version: {{ data.fw_rev }}</div>
          <div>IDF version: {{ data.idf_rev }}</div>
          <div>Build date: {{ data.build_date }}</div>
          <div>Serial number: {{ data.ser_num }}</div>
        </div>
      </div>
    </q-card-section>
    <q-card-actions>
      <q-btn flat v-on:click="SendAndRequest(data, 1, 0, 'mykey', true)">Apply</q-btn>
      <q-btn flat v-on:click="SendAndRequest(data, 1, 1, 'mykey', true)">Save</q-btn>
      <q-btn flat v-on:click="SendAndRequest(data, 1, 2, 'mykey', true)">Save&Reboot</q-btn>
    </q-card-actions>

  </q-card>
</template>

<script setup>
import { reactive } from "vue";
import { SendAndRequest } from "boot/network";

defineOptions({
  name: 'SystemCard'
})
const init = {
  net_bios_name: "", sys_name: "", sys_pass: "",
  model_name: "", hw_rev: 0, fw_rev: "", idf_rev: "", build_date: "", ser_num: ""
}
const data = reactive(init);
SendAndRequest(data, 2, 0, 'mykey', false);
</script>

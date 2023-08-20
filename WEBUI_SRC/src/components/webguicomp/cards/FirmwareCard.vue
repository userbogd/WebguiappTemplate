<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">FIRMWARE</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <q-toggle :dense="true" v-model="data.ota_enab" label="Eanble OTA autoudate" />
          <q-toggle :dense="true" v-model="data.res_ota_enab" label="Enable reset after update" />
          <q-input :dense="true" v-model="data.ota_url" label="OTA firmware file URL" />
          <q-input :dense="true" v-model="data.ota_auto_int" label="New firmware check interval, sec" />
          <div>Current firmware version:: {{ data.fw_rev }}</div>
          <div>Available firmware version:: {{ data.fw_rev }}</div>
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
  name: 'FirmwareCard'
})

const init = {
  ota_enab: false, res_ota_enab: false, ota_url: "", ota_auto_int: 0, fw_rev: ""
}

const data = reactive(init);
SendAndRequest(data, 2, 0, 'mykey', false);

</script>

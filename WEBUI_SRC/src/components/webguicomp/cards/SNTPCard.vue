<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">SNTP</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <q-toggle :dense="true" v-model="data.sntp_enab" label="Eanble SNTP" />
          <q-input :dense="true" v-model="data.sntp_serv1" label="SNTP server 1:" />
          <q-input :dense="true" v-model="data.sntp_serv2" label="SNTP server 2:" />
          <q-input :dense="true" v-model="data.sntp_serv3" label="SNTP server 3:" />
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



const init = {
  sntp_serv1: "",
  sntp_serv2: "",
  sntp_serv3: "",
  sntp_enab: false
}

const data = reactive(init);
SendAndRequest(data, 2, 0, 'mykey', false);
</script>

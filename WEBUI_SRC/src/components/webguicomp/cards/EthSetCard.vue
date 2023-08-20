<template>
  <q-card flat bordered class="card" v-show="data.eth_visible">
    <q-card-section>
      <div class="text-h6">ETHERNET</div>
    </q-card-section>

    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <q-toggle :dense="true" v-model="data.eth_enab" label="Ethernet enable" />
          <q-input :dense="true" v-model="data.eth_ip" label="IP address:" />
          <q-input :dense="true" v-model="data.eth_mask" label="Subnet mask:" />
          <q-input :dense="true" v-model="data.eth_gw" label="Gateway address:" />
          <q-toggle :dense="true" v-model="data.eth_isdhcp" label="DHCP enabled"></q-toggle>
          <q-input :dense=true v-model="data.eth_dns1" label="DNS1:" />
          <q-input :dense=true v-model="data.eth_dns2" label="DNS2:" />
          <q-input :dense=true v-model="data.eth_dns3" label="DNS3:" />
          <q-input :dense=true v-model="data.eth_mac" label="MAC:" />
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
  name: 'EthSetCard'
})

const init = {
  eth_visible: false,
  eth_enab: true, eth_isdhcp: true, eth_ip: "", eth_mask: "",
  eth_gw: "", eth_dns1: "", eth_dns2: "", eth_dns3: "", eth_mac: ""
}
const data = reactive(init);
SendAndRequest(data, 2, 0, 'mykey', false);
</script>

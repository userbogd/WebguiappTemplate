<template>
  <q-card flat bordered class="card">
    <q-card-section>
      <div class="text-h6">WiFi</div>
    </q-card-section>

    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <div class="q-gutter-md q-pa-none q-pb-none">
          <q-toggle :dense="true" v-model="data.wifi_enab" label="WiFi enable" />
          <q-btn :dense="true" label="Scan WiFi" @click="OpenScanDialog()"></q-btn>
          <q-select :dense="true" v-model="wifimodestr" :options="wifimodes" :map-options="true" :emit-value="true"
            label="WiFi mode"></q-select>
          <q-input :dense="true" v-model="wifipwr" label="Max power, dBm" />
          <q-input :dense="true" v-model="data.wifi_ap_ssid" label="WiFi network name(AP):" />
          <q-input :dense="true" v-model="data.wifi_ap_key" label="WiFi network key(AP):" />
          <q-input :dense="true" v-model="data.wifi_ap_ip" label="IP address(AP):" />
          <q-input :dense="true" v-model="data.wifi_sta_ssid" label="WiFi network name(CLN):" />
          <q-input :dense="true" v-model="data.wifi_sta_key" label="WiFi network key(CLN):" />
          <q-toggle :dense="true" v-model="data.wifi_isdhcp" label="DHCP enabled"></q-toggle>
          <q-input :dense="true" v-model="data.wifi_sta_ip" label="IP address(CLN):" />
          <q-input :dense="true" v-model="data.wifi_sta_mask" label="Subnet mask(CLN):" />
          <q-input :dense="true" v-model="data.wifi_sta_gw" label="Gateway address(CLN):" />
          <q-input :dense=true v-model="data.wifi_dns1" label="DNS1:" />
          <q-input :dense=true v-model="data.wifi_dns2" label="DNS2:" />
          <q-input :dense=true v-model="data.wifi_dns3" label="DNS3:" />
          <q-input :dense=true v-model="data.wifi_sta_mac" label="MAC(CLN):" />
          <q-input :dense=true v-model="data.wifi_ap_mac" label="MAC(AP):" />
        </div>
      </div>
    </q-card-section>
    <CardActions :senddata="data"></CardActions>
  </q-card>
</template>

<script setup>
import { computed, reactive } from "vue";
import { SendAndRequest } from "components/webguicomp/network";
import { useQuasar } from 'quasar'
import SelectWiFiDialog from 'components/webguicomp/SelectWiFiDialog.vue'
import CardActions from "components/webguicomp/CardActions.vue"

const $q = useQuasar();
defineOptions({
  name: 'WifiSetCard'
})

const init = {
  wifi_enab: true, wifi_mode: 1, wifi_power: 0, wifi_ap_ssid: "", wifi_ap_key: "",
  wifi_ap_ip: "", wifi_sta_ssid: "", wifi_sta_key: "", wifi_isdhcp: true, wifi_sta_ip: "",
  wifi_sta_mask: "", wifi_sta_gw: "", wifi_dns1: "", wifi_dns2: "", wifi_dns3: "",
  wifi_sta_mac: "", wifi_ap_mac: ""
}
const wifimodes = [
  { label: 'Station (STA)', value: '1' },
  { label: 'Access point (AP)', value: '2' },
  { label: 'Mixed mode (AP+STA)', value: '3' }];

const data = reactive(init);


const wifimodestr = computed({
  get() { return (data.wifi_mode).toString() },
  set(val) { data.wifi_mode = Number(val); }
})
const wifipwr = computed({
  get() { return (data.wifi_power) / 4 },
  set(val) { data.wifi_power = val * 4; }
})

function OpenScanDialog() {
  $q.dialog({
    component: SelectWiFiDialog
  });
};

SendAndRequest(data, 2, 0, 'mykey', false);


</script>

<template>
  <q-dialog ref="dialogRef" @hide="onDialogHide">
    <q-card class="q-dialog-plugin">
      <div class="q-pa-md q-gutter-md">
        <q-card-section>
          <q-inner-loading :showing="visible" label="Scaning WiFi..." label-class="text-teal"
            label-style="font-size: 1.1em" />
        </q-card-section>
        <q-card-section>
          <q-table title="WiFi networks" :rows="scandata.wifi_scan_res" :columns="columns" row-key="ssid"
            hide-no-data="true" wrap-cells="true" @row-click="ClickOnRaw" />
        </q-card-section>
        <q-card-actions>
          <q-btn label="OK" @click="onOKClick" />
          <q-btn label="Cancel" @click="onDialogCancel" />
        </q-card-actions>
      </div>
    </q-card>
  </q-dialog>
</template>

<script setup>
import { useDialogPluginComponent } from 'quasar'
import { PostData } from "boot/network";
import { reactive, ref } from 'vue';

defineEmits([
  // REQUIRED; need to specify some events that your
  // component will emit through useDialogPluginComponent()
  ...useDialogPluginComponent.emits
])

const { dialogRef, onDialogHide, onDialogOK, onDialogCancel } = useDialogPluginComponent()
// dialogRef      - Vue ref to be applied to QDialog
// onDialogHide   - Function to be used as handler for @hide on QDialog
// onDialogOK     - Function to call to settle dialog with "ok" outcome
//                    example: onDialogOK() - no payload
//                    example: onDialogOK({ /*...*/ }) - with payload
// onDialogCancel - Function to call to settle dialog with "cancel" outcome

// this is part of our example (so not required)
function onOKClick() {
  // on OK, it is REQUIRED to
  // call onDialogOK (with optional payload)
  onDialogOK()
  // or with payload: onDialogOK({ ... })
  // ...and it will also hide the dialog automatically
}

function ClickOnRaw(evt, row, index) {
  alert(`clicked SSID ${row.ssid}`)
}

function onDataReady() {
  visible.value = false;
}
let visible = ref(true);
const scandata = reactive({ wifi_scan_res: 10 });
PostData({ wifi_scan: 1 }, 2, 0, () => { });
setTimeout(() => { PostData(scandata, 2, 0, () => onDataReady()) }, 7000);

const columns = [
  { name: 'ssid', label: 'SSID', align: 'left', field: 'ssid', sortable: true },
  { name: 'rssi', label: 'RSSI', field: 'rssi', sortable: true },
  { name: 'ch', label: 'CHANNEL', field: 'ch', sortable: true },
]
</script>

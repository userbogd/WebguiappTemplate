<template>
  <q-card flat class="card">
    <q-card-section>
      <div class="text-h6">Color picker</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="q-pa-md">
        <q-color v-model="hex" :format-model="rgb" @change="UpdateColor" />
      </div>
      <div class="colorPicker"></div>
    </q-card-section>
  </q-card>
</template>

<script setup>
import { computed, onUnmounted, reactive, onMounted, ref } from "vue";
import { PostData } from "components/webguicomp/network";
import iro from '@jaames/iro';

var colorPicker;

defineOptions({
  name: 'ColorCard'
})
let hex = ref('#335566');
const init = {
  RGB: { R: 0, G: 0, B: 0 }
}

function UpdateColor() {
  console.log(hex.value);
  let m = hex.value.match(/^#([0-9a-f]{6})$/i)[1];
  console.log(m);
  if (m) {
    data.RGB.R = parseInt(m.substr(0, 2), 16);
    data.RGB.G = parseInt(m.substr(2, 2), 16);
    data.RGB.B = parseInt(m.substr(4, 2), 16);
    PostData(data, 1, 0, null);
  }
}

onMounted(() => {
  colorPicker = new iro.ColorPicker(".colorPicker", {
    width: 280,
    color: "rgb(255, 0, 0)",
    borderWidth: 1,
    borderColor: "#fff",
  });
  colorPicker.on('color:change', function (color) {
    // log the current color as a HEX string
    hex.value = color.hexString;
    UpdateColor();
  });
})



const data = reactive(init);
PostData(data, 2, 0, null);

</script>

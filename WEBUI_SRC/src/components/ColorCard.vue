<template>
  <q-card flat class="card">
    <q-card-section>
      <div class="text-h6">Color picker</div>
    </q-card-section>
    <q-card-section class="q-pt-none">
      <div class="row justify-center">
        <div class="q-pa-xs col-auto">
          <div class="colorPicker"></div>
          <div class="q-mt-md" id="values"></div>
        </div>
      </div>
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

const init = {
  color: { r: 0, g: 0, b: 0 }
}

onMounted(() => {
  colorPicker = new iro.ColorPicker(".colorPicker", {
    width: 300,
    color: "rgb(64, 128, 64)",
    borderWidth: 1,
    borderColor: "#ffffff",
    layout: [
      {
        component: iro.ui.Box,
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'value',
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'saturation'
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          id: 'hue-slider',
          sliderType: 'hue'
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'kelvin',
          minTemperature: 3600,
          maxTemperature: 9600
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'red'
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'green'
        }
      },
      {
        component: iro.ui.Slider,
        options: {
          sliderType: 'blue'
        }
      },
    ]
  });
  colorPicker.on('input:end', function (color) {
    data.color = color.rgb;
    PostData(data, 1, 0, null);
  });
  var values = document.getElementById("values");
  colorPicker.on(["color:init", "color:change"], function (color) {
    values.innerHTML = [
      "hex: " + color.hexString,
      "rgb: " + color.rgbString,
      "hsl: " + color.hslString,
    ].join("<br>");
  });

})
const data = reactive(init);
PostData(data, 2, 0, null);
</script>

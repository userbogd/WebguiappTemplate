<template>
  <div class="cardholder">
    <WifiSetCard></WifiSetCard>
    <EthSetCard></EthSetCard>
    <GSMSetCard></GSMSetCard>
    <SerialCard></SerialCard>
    <LoRaSetCard></LoRaSetCard>
  </div>
</template>

<script setup>
import WifiSetCard from "components/webguicomp/cards/WifiSetCard.vue";
import EthSetCard from "components/webguicomp/cards/EthSetCard.vue";
import GSMSetCard from "src/components/webguicomp/cards/GSMSetCard.vue";
import LoRaSetCard from "src/components/webguicomp/cards/LoRaSetCard.vue";
import SerialCard from "src/components/webguicomp/cards/SerialCard.vue";

defineOptions({
  name: 'InterfacesSettings'
})
</script>

<template>
  <div class="cardholder">
    <WifiSetCard></WifiSetCard>
    <EthSetCard></EthSetCard>
    <GSMSetCard></GSMSetCard>
    <LoRaSetCard></LoRaSetCard>
  </div>
</template>

<script setup>
import WifiSetCard from "components/webguicomp/cards/WifiSetCard.vue";
import EthSetCard from "components/webguicomp/cards/EthSetCard.vue";
import GSMSetCard from "src/components/webguicomp/cards/GSMSetCard.vue";
import LoRaSetCard from "src/components/webguicomp/cards/LoRaSetCard.vue";

defineOptions({
  name: 'InterfacesSettings'
})
</script>

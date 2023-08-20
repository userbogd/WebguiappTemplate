<template>
  <div class="cardholder">
    <WifiSetCard></WifiSetCard>
    <EthSetCard></EthSetCard>
  </div>
</template>

<script setup>
import WifiSetCard from "components/webguicomp/cards/WifiSetCard.vue";
import EthSetCard from "components/webguicomp/cards/EthSetCard.vue";

defineOptions({
  name: 'InterfacesSettings'
})
</script>

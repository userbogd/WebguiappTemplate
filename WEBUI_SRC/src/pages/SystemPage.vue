<template>
  <div class="cardholder">
    <SystemCard></SystemCard>
    <FirmwareCard></FirmwareCard>
    <StatCard></StatCard>
  </div>
</template>

<script setup>
import SystemCard from "components/webguicomp/cards/SystemCard.vue";
import FirmwareCard from "components/webguicomp/cards/FirmwareCard.vue";
import StatCard from "components/webguicomp/cards/StatCard.vue";

defineOptions({
  name: 'SystemPage'
})
</script>

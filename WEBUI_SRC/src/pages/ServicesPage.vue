<template>
  <div class="cardholder">
    <SNTPCard></SNTPCard>
    <CronCard></CronCard>
    <AstroTimerCard></AstroTimerCard>
    <MQTT1Card></MQTT1Card>
    <MQTT2Card></MQTT2Card>
  </div>
</template>

<script setup>
import SNTPCard from "components/webguicomp/cards/SNTPCard.vue";
import MQTT1Card from "components/webguicomp/cards/MQTT1Card.vue";
import MQTT2Card from "components/webguicomp/cards/MQTT2Card.vue";
import CronCard from "src/components/webguicomp/cards/CronCard.vue";
import AstroTimerCard from "src/components/webguicomp/cards/AstroTimerCard.vue";

defineOptions({
  name: 'ServicesPage'
})
</script>

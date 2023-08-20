<template>
  <div class="cardholder">
    <SNTPCard></SNTPCard>
    <MQTT1Card></MQTT1Card>
    <MQTT2Card></MQTT2Card>
  </div>
</template>

<script setup>
import SNTPCard from "components/webguicomp/cards/SNTPCard.vue";
import MQTT1Card from "components/webguicomp/cards/MQTT1Card.vue";
import MQTT2Card from "components/webguicomp/cards/MQTT2Card.vue";

defineOptions({
  name: 'ServicesPage'
})
</script>

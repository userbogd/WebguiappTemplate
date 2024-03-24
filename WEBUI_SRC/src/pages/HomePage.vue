<template>
  <div class="cardholder">
    <HomeCard></HomeCard>
  </div>
</template>

<script setup>
import HomeCard from "src/components/webguicomp/cards/HomeCard.vue";
import { defineComponent } from "vue";

defineOptions({
  name: 'HomePage'
})
</script>

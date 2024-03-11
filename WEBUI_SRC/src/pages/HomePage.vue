<template>
  <div class="cardholder">
    <FilesCard></FilesCard>
  </div>
</template>

<script setup>
import FilesCard from "src/components/webguicomp/cards/FilesCard.vue";
import { defineComponent } from "vue";

defineOptions({
  name: 'HomePage'
})
</script>

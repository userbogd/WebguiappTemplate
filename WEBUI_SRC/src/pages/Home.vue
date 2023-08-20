<template>
  <div class="cardholder">
    <HomeCard></HomeCard>
  </div>
</template>

<script>
import HomeCard from "components/webguicomp/cards/HomeCard.vue";
import { defineComponent } from "vue";

export default defineComponent({
  name: "HomePage",
  components: { HomeCard }
});
</script>

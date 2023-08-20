<template>
  <q-card-actions>
    <q-btn flat v-on:click="SendAndRequest(senddata, 1, 0, 'mykey', true)">Apply</q-btn>
    <q-btn flat v-on:click="SendAndRequest(senddata, 1, 1, 'mykey', true)">Save</q-btn>
    <q-btn flat v-on:click="SendAndRequest(senddata, 1, 2, 'mykey', true)">Save&Reboot</q-btn>
  </q-card-actions>
</template>

<script setup>
import { SendAndRequest } from "boot/network";
</script>

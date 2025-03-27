<template>
    <div class="list-container">
        <h2 class="list-title">Liste des capteurs : </h2>
        <div>
            <CardSensor v-for="(sensor, index) in sensors" v-bind:key="index" :sensor="sensor" />
        </div>
    </div>
</template>

<script setup>
import { ref } from "vue";
import CardSensor from './CardSensor.vue'

const sensors = ref([
    {
        id: 1,
        humidity: '15%',
        temperature: '18°C',
        last_info: "27/03/2025 11h58"
    },
    {
        id: 2,
        humidity: '15%',
        temperature: '18°C',
        last_info: "27/03/2025 11h58"
    },
    {
        id: 3,
        humidity: '15%',
        temperature: '18°C',
        last_info: "27/03/2025 11h58"
    },
    {
        id: 4,
        humidity: '15%',
        temperature: '18°C',
        last_info: "27/03/2025 11h58"
    },
    {
        id: 5,
        humidity: '15%',
        temperature: '18°C',
        last_info: "27/03/2025 11h58"
    }
])

</script>

<style scoped>
.list-container {
    margin-left: 50px;
    display: flex;
    flex-direction: column;
    align-items: center;
    margin-top: 15px;
}

.list-title {
    font-size: 20px;
    font-style: oblique;
}
</style>
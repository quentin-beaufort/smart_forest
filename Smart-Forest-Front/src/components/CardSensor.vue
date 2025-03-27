<template>
    <div class="card-container">
        <div class="card-infos">
            <p>Id </p>
            <p>{{ sensor.id }}</p>
        </div>

        <div class="card-info">
            <p>Température</p>
            <p>{{ sensor.temperature }}</p>
        </div>

        <div class="card-info">
            <p>Humiditié</p>
            <p>{{ sensor.humidity }}</p>
        </div>

        <div class="card-info">
            <p>Données reçu pour la derniere fois</p>
            <p>{{ sensor.last_info }}</p>
        </div>
    </div>
</template>

<script setup>

const props = defineProps(['sensor'])


</script>

<style scoped>
.card-container {
    display: flex;
    justify-content: space-around;
    width: 500px;
    box-shadow: rgba(17, 12, 46, 0.15) 0px 48px 100px 0px;
    margin-bottom: 15px;
    padding: 10px;
    border-radius: 10px;
    background-color: #2FD09C;
    color: white;
}

.card-infos {
    display: flex;
    flex-direction: column;
}
</style>
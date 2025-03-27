import axios from "axios"

export const api = axios.create({
    baseURL: 'https://smartforest.eu2.cloud.thethings.industries/api/v3/as/applications/smart-forest',
    headers: {
        Accept: 'text/event-stream'
    }
})
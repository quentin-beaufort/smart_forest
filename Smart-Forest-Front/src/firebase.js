// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyBm4FvsS3Nf9QP7Y9hSvG-9lcuFxu1YtE8",
  authDomain: "smart-forest-7012e.firebaseapp.com",
  databaseURL: "https://smart-forest-7012e-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "smart-forest-7012e",
  storageBucket: "smart-forest-7012e.firebasestorage.app",
  messagingSenderId: "141789120442",
  appId: "1:141789120442:web:0fe9de606fc5be7f1b3f83",
  measurementId: "G-PBFPW7FHLG"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const db = getDatabase(app)
export default {app, db , analytics} 

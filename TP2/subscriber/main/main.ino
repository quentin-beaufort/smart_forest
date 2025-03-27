#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "INPUT YOUR SSID HERE";
const char* password = "INPUT YOUR PASSWORD HERE";

// MQTT Conf
const char* mqtt_server = "INPUT YOUR MQTT IP HERE";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

const int redPin = 32;    // G32
const int greenPin = 33;  // G33
const int bluePin = 25;   // G25

// Temperature thresholds
const float LOW_TEMP = 21.0;   // Full blue
const float HIGH_TEMP = 26.0;  // Full red

// Time tracking for connection monitoring
unsigned long lastConnectionCheck = 0;
const long connectionInterval = 5000;  // Check connection every 5 seconds

// MQTT Settings
#define MQTT_KEEPALIVE 30      // Seconds between keepalive messages
const char* clientIdPrefix = "ESP32_Client_";
String uniqueClientId;         // Will store the unique client ID

void callback(const char* topic, byte* payload, unsigned int length) {
  Serial.println("Message received on topic: " + String(topic));
  
  char tempStr[length + 1];
  memcpy(tempStr, payload, length);
  tempStr[length] = '\0';
  
  float temperature = atof(tempStr);
  
  Serial.print("Temperature received: ");
  Serial.println(temperature);
  
  int redValue, greenValue, blueValue;
  
  if (temperature <= LOW_TEMP) {
    // Full blue for temperatures at or below 21°C
    redValue = 0;
    greenValue = 0;
    blueValue = 255;
  } else if (temperature >= HIGH_TEMP) {
    // Full red for temperatures at or above 26°C
    redValue = 255;
    greenValue = 0;
    blueValue = 0;
  } else {
    // Gradient between blue and red for temperatures between 21°C and 26°C
    float ratio = (temperature - LOW_TEMP) / (HIGH_TEMP - LOW_TEMP);
    redValue = ratio * 255;
    blueValue = (1 - ratio) * 255;
    greenValue = 0;
  }
  
  // Set LED colors
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
  
  Serial.printf("LED set to R:%d G:%d B:%d\n", redValue, greenValue, blueValue);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== ESP32 MQTT Temperature LED Controller ===");
  
  // Initialize LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Set initial LED off state
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
  delay(1000);
  
  // WiFi connection
  Serial.print("Connexion au WiFi...");
  WiFi.disconnect(true);  // Disconnect from wifi to set new wifi connection
  WiFi.mode(WIFI_STA);    // Init wifi mode
  
  // for WPA2-Enterprise, declare username before
  // WiFi.begin(ssid, WPA2_AUTH_PEAP, username, username, password);
  WiFi.begin(ssid, password);
  
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    Serial.print(".");
    delay(500);
    wifiAttempts++;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nÉchec de connexion WiFi après plusieurs tentatives. Redémarrage...");
    ESP.restart();
  }
  
  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
  
  // Create a unique client ID by appending the last 8 characters of the MAC address
  String macAddress = WiFi.macAddress();
  macAddress.replace(":", ""); // Remove colons from MAC address
  uniqueClientId = clientIdPrefix + macAddress.substring(6);
  Serial.print("Client ID MQTT unique : ");
  Serial.println(uniqueClientId);
  
  // Instantiating MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.setKeepAlive(MQTT_KEEPALIVE);
  client.setSocketTimeout(10); // Shorter socket timeout for faster detection of connection issues
  
  // Initial MQTT connection
  reconnectMQTT();
  
  // Blink LED to indicate successful connection
  for (int i = 0; i < 3; i++) {
    analogWrite(greenPin, 100);
    delay(200);
    analogWrite(greenPin, 0);
    delay(200);
  }
}

void reconnectMQTT() {
  int attempts = 0;
  
  Serial.println("Tentative de connexion MQTT...");
  
  while (!client.connected() && attempts < 3) {
    attempts++;
    Serial.print("Tentative #");
    Serial.print(attempts);
    Serial.print("...");
    
    // Connect with persistent session (clean session = false)
    if (client.connect(uniqueClientId.c_str(), NULL, NULL, NULL, 0, true, NULL, false)) {
      Serial.println("Connecté au broker MQTT!");
      
      // Subscribe with QoS 1 for more reliable delivery
      if (client.subscribe("esp32/temperature", 1)) {
        Serial.println("Abonné au topic: esp32/temperature (QoS 1)");
      } else {
        Serial.println("Échec d'abonnement au topic");
      }
    } else {
      Serial.print("Échec, erreur : ");
      Serial.print(client.state());
      Serial.println(" (nouvelle tentative dans 2s)");
      delay(2000);
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check MQTT connection status periodically
  if (currentMillis - lastConnectionCheck >= connectionInterval) {
    lastConnectionCheck = currentMillis;
    
    // Check both WiFi and MQTT connection
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connexion WiFi perdue. Tentative de reconnexion...");
      WiFi.reconnect();
    } else if (!client.connected()) {
      Serial.println("Connexion MQTT perdue. Tentative de reconnexion...");
      reconnectMQTT();
    }
  }
  client.loop();
}
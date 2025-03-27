#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ENTER YOUR SSID";
const char* password = "ENTER YOUR SSID PASSWORD";

const char* mqtt_server = "ENTER IP OF THE BROKER";
const int mqtt_port = 1883;
const char* mqtt_topic_temp = "esp32/temperature";

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 21
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation du DHT11...");
  delay(5000);

  // 🔌 Connexion au Wi-Fi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.print("Connexion au WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  reconnectMQTT();


  dht.begin();
  delay(2000);
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connexion au broker MQTT... ");
    if (client.connect("ESP32_Client")) {
      Serial.println("Connecté !");
      client.publish("esp32/status", "ESP32 connecté !");
    } else {
      Serial.print("Échec, erreur : ");
      Serial.print(client.state());
      Serial.println(" (nouvelle tentative dans 5s)");
      delay(5000);
    }
  }
}


void loop() {
  delay(2000);

  client.loop();

  client.publish("esp32/test", "Hello MQTT!");
  Serial.println(" test!");

  float temperature = dht.readTemperature(); // Température en °C

  if (isnan(temperature)) {
    Serial.println("Erreur de lecture du DHT11 !");
    Serial.println(dht.readTemperature());
    delay(2000);
    return;
  }

  Serial.print("🌡️ Température : ");
  Serial.print(temperature);
  Serial.println(" °C");

  client.publish("esp32/temperature", String(temperature).c_str());

  delay(5000);

}

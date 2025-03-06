#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WiFi@YNOV";

const char* password = "MDP";
const char* username = "Email";

// ⚡ Configuration du broker MQTT
const char* mqtt_server = "IP PERSO";  // Remplace par ton broker MQTT
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(5000);

  // 🔌 Connexion au Wi-Fi
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA);    //init wifi mode
  WiFi.begin(ssid, WPA2_AUTH_PEAP, username, username, password);
  Serial.print("Connexion au WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    Serial.print(WiFi.status());
    delay(500);
  }

  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  // 🔗 Connexion au broker MQTT
  client.setServer(mqtt_server, mqtt_port);
  reconnectMQTT();
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
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // 📡 Envoi d'un message MQTT toutes les 5 secondes
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    String message = "Hello MQTT!";
    Serial.println("Envoi MQTT : " + message);
    client.publish("esp32/test", message.c_str());
  }
}

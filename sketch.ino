#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

const char* topic_temp = "emri123/iot/temperature";
const char* topic_hum  = "emri123/iot/humidity";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" OK!");
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String id = "esp32-" + String(random(0xffff), HEX);
    if (client.connect(id.c_str())) {
      Serial.println(" OK!");
    } else {
      Serial.println(" failed, retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWiFi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) connectMQTT();
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor reading error!");
  } else {
    Serial.printf("Temperature: %.1f C, Humidity: %.1f %%\n", t, h);
    client.publish(topic_temp, String(t).c_str());
    client.publish(topic_hum, String(h).c_str());
  }
  delay(3000);
}

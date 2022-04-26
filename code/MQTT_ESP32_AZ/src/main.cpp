#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>

DHT my_sensor(17, DHT22);
WiFiClient espClient;
PubSubClient client(espClient);

float value1, value2;
const char* ssid = "home-sweet-home";
const char* password = "58413072613092673805";
const char* mqtt_server = "81.169.194.117";
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
  }

randomSeed(micros());

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (u32_t i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
    Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "student", "iotproject2§&d")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

    //pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    Serial.begin(9600);
    my_sensor.begin();
    setup_wifi();
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    client.setServer(mqtt_server, 1883);
    client.connect(clientId.c_str(), "student", "iotproject2§&d");
    client.setCallback(callback);
}

void loop() {
    
    value1 = my_sensor.readTemperature();   // temperature
    value2 = my_sensor.readHumidity();      // humidity
    

    Serial.print("Temperature: ");
    Serial.print(value1);
    Serial.print(" °C / Humidity: ");
    Serial.print(value2);
    Serial.println( " %");

    delay(2000);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "%2.2f", value1);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("dhbw/team12/value1", msg);
    snprintf (msg, MSG_BUFFER_SIZE, "%2.2f", value2);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("dhbw/team12/value2", msg);

  }
}
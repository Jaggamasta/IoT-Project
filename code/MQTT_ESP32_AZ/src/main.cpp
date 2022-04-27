#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLSVGc8NTw"                        // enter the correct ID from your template from blynk console cloud 
#define BLYNK_DEVICE_NAME "IoTProjectTeam12"                    // enter your device name from blynk console cloud
#define BLYNK_AUTH_TOKEN "yJBOd-8062LDX76ddXkBCJUWL5nEZYoH"     // enter your auth token from the blynk console cloud

#define BLYNK_PRINT Serial              // Coomment this out to disable prints and save space

// You schould get Auth Token in the Blynk App
// Got to the Project Settings (nut icon)
const char* auth = BLYNK_AUTH_TOKEN;          // blynk auth token from the blynk app
// Your WiFi credentials
// Set password to "" open networks
const char* ssid = "home-sweet-home";        // your network name
const char* pass = "58413072613092673805";   // your wifi password


DHT my_sensor(17, DHT22);
WiFiClient espClient;
PubSubClient client(espClient);

float value1, value2;

BlynkTimer timer;

//const char* ssid = "home-sweet-home";
//const char* password = "58413072613092673805";
const char* mqtt_server = "81.169.194.117";
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
//int value = 0;

void setup_wifi() {

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

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

// this function is called every time the device is connected to the blynk.cloud
/*BLYNK_CONNECTED(){

    // change weblink button message to "Congratulations!"
    Blynk.setProperty(V3, "offimageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
    Blynk.setProperty(V3, "onimageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
    Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}
*/

// this function sends Arduino's uptime every second to virtual pin 2.
void myTimerEvent(){

    // you can send any value at any time.
    // please don't send more than 10 values per second.
    Blynk.virtualWrite(V0, value1);
    Blynk.virtualWrite(V1, value2);
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
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);      // Blynk.begin(auth, ssid, pass, IPAdress(192.168.1.100), 8080)
    timer.setInterval(1000L, myTimerEvent);     // setup a unction to be calles every second

}

void loop() {
    
    Serial.print("Temperature: ");
    Serial.print(value1);
    Serial.print(" °C / Humidity: ");
    Serial.print(value2);
    Serial.println( " %");

    value1 = my_sensor.readTemperature();   // temperature
    value2 = my_sensor.readHumidity();      // humidity

    Blynk.run();
    timer.run();

    delay(1000);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //unsigned long now = millis();
  //if (now - lastMsg > 2000) {
  //  lastMsg = now;
  //  ++value;
    //snprintf (msg, MSG_BUFFER_SIZE, "%2.2f", value1);
    //Serial.print("Publish message: ");
    //Serial.println(msg);
    client.publish("dhbw/team12/value1", String(value1).c_str(), true); // statt msg true
    //snprintf (msg, MSG_BUFFER_SIZE, "%2.2f", value2);
    //Serial.print("Publish message: ");
    //Serial.println(msg);
    client.publish("dhbw/team12/value2", String(value2).c_str(), true); // statt msg true
    

    delay(1000);
 // }
}
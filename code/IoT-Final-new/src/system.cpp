// Copyright (C) <2022> by [...]
#include "system.h"
#include "WiFiClient.h"
#include "config.h"
#include <Arduino.h>

/**
 * General System super-loop
 * Same as `void loop()` but only for the project
 */
void IoTSystem::loop() {
    // <-- USER CODE GOES HERE -->
    
}

IoTSystem::IoTSystem(
        char *_ssid,
        char *_pwd,
        char *_blynk_auth,
        LiquidCrystal_I2C lcd,
        DHT dht,
        WiFiClient espClient,
        PubSubClient client
) :
    _ssid(_ssid),
    _pwd(_pwd),
    _blynk_auth((char *) _blynk_auth),
    lcd(lcd),
    my_sensor(dht),
    espClient(espClient),
    client(client)
{
    // "Normal" constructor
}


/**
 * Setup wifi with SSID and Password
 */
void IoTSystem::setup_wifi() {
    // WiFi setup code
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(this->_ssid);

    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(this->_ssid, this->_pwd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

/**
 * Setup necessary pins for System
 */
void IoTSystem::setup_pins() {
    // Pin setup code
}

/**
 * Setup LCD Screen
 */
void IoTSystem::setup_lcd() {
    // LCD setup code
    lcd = LiquidCrystal_I2C(0x27, 16, 2);
}

/**
 * Setup Blynk server with auth
 */
void IoTSystem::setup_blynk() {
    // Blynk setup code
}

void IoTSystem::setup_sensors() {
    my_sensor = DHT(17, DHT22);
}

/**
 * Setup MQTT server
 */
void IoTSystem::setup_mqtt() {
    // MQTT setup code
    client = PubSubClient(espClient);
}

/**
 * Get SSID string of connected WiFi network
 */
String IoTSystem::get_ssid() {
    return String(this->_ssid);
}

/**
 * Get authentication token for Blynk
 */
String IoTSystem::get_blynk_auth() {
    return String(this->_blynk_auth);
}

/**
 * Get temperature of current tool
 *
 * @return float temperature of current tool
 */
float IoTSystem::get_temperature() {
    return this->temperature;
}

/**
 * Get humidity of the system
 *
 * @return float humidity
 */
float IoTSystem::get_humidity() {
    return this->humidity;
}

/**
 * Get current fluid level for cooling
 *
 * @return float cooling fluid level
 */
float IoTSystem::get_fluid_level() {
    return this->fluid_level;
}


void IoTSystem::rfid_read() {

}

void IoTSystem::publish_data() {
    client.publish("dhbw/team12/value1", String(temperature).c_str(), true); // statt msg true
    client.publish("dhbw/team12/value2", String(humidity).c_str(), true); // statt msg true 
    client.publish("dhbw/team12/value3", String(fluid_level).c_str(), true);
}

void IoTSystem::publish_data(float _value1, float _value2, float _value3) {
    client.publish("dhbw/team12/value1", String(_value1).c_str(), true); // statt msg true
    client.publish("dhbw/team12/value2", String(_value2).c_str(), true); // statt msg true 
    client.publish("dhbw/team12/value3", String(_value3).c_str(), true); 
}

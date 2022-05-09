// Copyright (C) <2022> by ...
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <cstdint>
#include "system.h"
#include "config.h"



LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT my_sensor(17, DHT22);
WiFiClient espClient;
PubSubClient client((Client&) espClient);
BlynkTimer timer;

IoTSystem iot(SSID, PASS, AUTH, lcd, my_sensor, espClient, client);

// value1 = Temperatur, value2 = Humidity, value3 = Fluid Level
// int value = 0;
void setup() {

}

void loop() {
    iot.loop();
}

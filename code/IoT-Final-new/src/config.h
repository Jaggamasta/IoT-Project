#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

// Your WiFi credentials
// Set password to "" open networks
#define SSID "home-sweet-home"    // your network name  "Eigenes WLAN haben du musst"
#define PASS "58413072613092673805" // your wifi password   "00000000"
// const char* ssid = "home-sweet-home";
// const char* password = "58413072613092673805";
//#define BLYNK_TEMPLATE_ID "TMPLyAyPxcki"                      // ID from Davids blynk project
//#define BLYNK_DEVICE_NAME "Template01"                        // Name from Davids blynk project
//#define BLYNK_AUTH_TOKEN "OWErakJ76NEjc2APznUTV3FPQEjEx-OC"   // Token from Davis blynk project
#define MQTT_SERVER "81.169.194.117"


// ----------------| BLYNK |----------------
#define BLYNK_PRINT Serial              // Coomment this out to disable prints and save space
#define BLYNK_TEMPLATE_ID "TMPLSVGc8NTw"                        // enter the correct ID from your template from blynk console cloud 
#define BLYNK_DEVICE_NAME "IoTProjectTeam12"                    // enter your device name from blynk console cloud
#define BLYNK_AUTH_TOKEN "yJBOd-8062LDX76ddXkBCJUWL5nEZYoH"     // enter your auth token from the blynk console cloud
#define AUTH BLYNK_AUTH_TOKEN          // blynk auth token from the blynk app


// Pin definitions
#define TRIG            13
#define ECHO            12
#define PUMP            15
#define ALARM_LED       16

// LCD 


// --------------| Sensor Values |--------------



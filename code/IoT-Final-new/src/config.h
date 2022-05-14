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
#include <Adafruit_NeoPixel.h>


// ------------ | WiFi credentials | --------------
// Set password to "" open networks
// your network name  
#define SSID            "home-sweet-home"  // "Eigenes WLAN haben du musst" for hotspot
// your wifi password   
#define PASS            "58413072613092673805" // "00000000" for hotspot
// DHBW MQTT server IP-adress
#define MQTT_SERVER     "81.169.194.117"
#define MQTT_PORT       1883

// ----------------| BLYNK |----------------

// Comment this out to disable prints and save space
#define BLYNK_PRINT         Serial
// enter the correct ID from your template from blynk console cloud 
#define BLYNK_TEMPLATE_ID   "TMPLSVGc8NTw"    
// enter your device name from blynk console cloud
#define BLYNK_DEVICE_NAME   "IoTProjectTeam12"  
// enter your auth token from the blynk console cloud                 
#define BLYNK_AUTH_TOKEN    "yJBOd-8062LDX76ddXkBCJUWL5nEZYoH" 
// blynk auth token from the blynk app    
#define AUTH                BLYNK_AUTH_TOKEN          

//#define BLYNK_TEMPLATE_ID "TMPLyAyPxcki"                      // ID from Davids blynk project
//#define BLYNK_DEVICE_NAME "Template01"                        // Name from Davids blynk project
//#define BLYNK_AUTH_TOKEN "OWErakJ76NEjc2APznUTV3FPQEjEx-OC"   // Token from Davis blynk project


// --------- | Pin definitions | ---------------
#define TRIG            13 // ultrasonic trigger
#define ECHO            12 // ultrasonic echo
#define PUMP            15 // relais & pump
#define ALARM_LED       16 // red alarm led & piezo
// Which pin on the Board is connected to the NeoPixels?
#define STRIP_PIN       2
// LCD 

#define LCD_COLS            16
#define LCD_ROWS            2
#define LCD_ADDR            0x27


// DHT Sensor

#define DHT_DATA_PIN        17

// Blynk

#define BLYNK_IP            "blynk.cloud"
#define BLYNK_PORT          80


// ------------- | NeoPixel RGB strip | -----------------

// How many NeoPixels are attached?
#define NUMPIXELS           20
// Time (in milliseconds) to pause between pixels
#define RGB_DELAY           5000 
// definition of the brightness level 0-50
#define BRIGHTNESS          30


// --------------| Sensor Values |--------------



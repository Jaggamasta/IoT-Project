// Copyright (C) <2022> by IoT-Project-Team-12-DHBW-Stuttgart-TWIE19B
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
#include <MFRC522.h>


// ---------------------------- | WiFi credentials | -----------------------------------
// Set password to "" open networks
// your network name  
#define SSID            "home-sweet-home"       //"ASQ Gastzugang"  "Eigenes WLAN haben du musst" for hotspot, "home-sweet-home"
// your wifi password   
#define PASS            "58413072613092673805"  //"ASQgast!15"       //"00000000" ,   for hotspot, 
// DHBW MQTT server IP-adress
#define MQTT_SERVER     "81.169.194.117"
#define MQTT_PORT       1883

// -------------------------------- | BLYNK | ------------------------------------------

// Comment this out to disable prints and save space
#define BLYNK_PRINT             Serial
// enter the correct ID from your template from blynk console cloud 
#define BLYNK_TEMPLATE_ID       "TMPLSVGc8NTw"    
// enter your device name from blynk console cloud
#define BLYNK_DEVICE_NAME       "IoTProjectTeam12"  
// enter your auth token from the blynk console cloud                 
#define BLYNK_AUTH_TOKEN        "yJBOd-8062LDX76ddXkBCJUWL5nEZYoH" 
// blynk auth token from the blynk app    
#define AUTH                    BLYNK_AUTH_TOKEN          

//#define BLYNK_TEMPLATE_ID "TMPLyAyPxcki"                      // ID from Davids blynk project
//#define BLYNK_DEVICE_NAME "Template01"                        // Name from Davids blynk project
//#define BLYNK_AUTH_TOKEN "OWErakJ76NEjc2APznUTV3FPQEjEx-OC"   // Token from Davis blynk project


/* ========================== | PIN DEFINITIONS | ====================================== */
#define TRIG                13 // ultrasonic trigger, white wire
#define ECHO                12 // ultrasonic echo, black wire
#define PUMP                15 // relais & pump
#define ALARM_PIEZO         16 // acoustic piezo alarm
#define STRIP_PIN           2  // RGB strip pin

// --------------------------- | motor pins | ---------------------------------------------
#define SPU             2048
#define IN1             32
#define IN2             33
#define IN3             25
#define IN4             26

// ------------------------- | motor delays | ----------------------------------------------
#define DELAY_WORK      5000
#define DELAY_TOOL      2000

// ----------------------- | rfid readers pins | -------------------------------------------
#define RST_PIN         4   // reset pin       
#define SS_1_PIN        5   // SDA pin reader 1 (0)        
#define SS_2_PIN        0   // SDA pin reader 2 (1)
#define SS_3_PIN        14   // SDA pin reader 3 (2)

/**  
SDA     GPIO 5, 0, 14    
SCK     GPIO 18
MOSI    GPIO 23
MISO    GPIO 19
RST     GPIO 4
GND     GROUND
3.3V    3.3V 
 */

// --------------------- | define reader amount | ------------------------------------------
#define NR_OF_READERS   3
#define NUM_UIDS        3

// -------------------- | reader uid definitions | -----------------------------------------

#define READER_0_UIDS   {\
    {0xA3, 0x42, 0x68, 0x39},\
    {0xC3, 0x77, 0x4A, 0x39},\
    0\
}\

#define READER_1_UIDS   {\
    {0xE6, 0xBD, 0xC6, 0x24},\
    0,\
    0\
}\

#define READER_2_UIDS   {\
    {0x93, 0x86, 0x9D, 0x39},\
    0,\
    0\
}\

// ------------------------------| LCD | ----------------------------------------------------

#define LCD_COLS        16
#define LCD_ROWS        2
#define LCD_ADDR        0x27
/** 
 * LCD pins
 *      SDA             21  black wire
 *      SCL             22  white wire
 * */ 

// -------------------------- | DHT Sensor | -------------------------------------------------

#define DHT_DATA_PIN    17

// ---------------------------- | Blynk | ----------------------------------------------------

#define BLYNK_IP        "blynk.cloud"
#define BLYNK_PORT      80


// -------------------- | NeoPixel RGB strip | ------------------------------------------------

// How many NeoPixels are attached?
#define NUMPIXELS           23
// Time (in milliseconds) to pause between pixels
#define RGB_DELAY           5000 
// definition of the brightness level 0-50
#define BRIGHTNESS          30


// -------------------- | Sensor Values | ------------------------------------------------------



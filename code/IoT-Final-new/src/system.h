// Copyright (C) <2022> by IoT-Project-Team-12-DHBW-Stuttgart-TWIE19B

#pragma once // referring included libraries once, preventing multiple declarations
// including all the necessary libraries for the project

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <Stepper.h>
#include <CheapStepper.h>
#include "config.h"
//#include <WiFiClientSecure.h>
//#include <UniversalTelegramBot.h>
//#include <ArduinoJson.h>



#define READER_0    0
#define READER_1    1
#define READER_2    2



/**
 * Operation areas of the system
 *
 * `IDLE`           -        System is on hold or 0 position
 * `OPERATING`      -        System is in the working area
 * `COOLING`        -        System is in the cooling state
 * `TOOl1 - TOOl3`  -        System is in the Tool container 1-3 
 */
typedef enum {
    IDLE,
    WORKING,
    COOLING,
    TOOL1,
    TOOL2,
    TOOL3,
} Operation;

/* ======= | declaration of the IoTSystem class | ====== */
class IoTSystem {
private:
    /* WiFi network SSID */
    char* _ssid;

    /* SSID Password */
    char* _pwd;

    /* Blynk authentication token */
    char* _blynk_auth;
    /* Current stepper motor position */
    int stepper_cur_pos;

    /* Current operation area of the tool */
    Operation cur_op;

    /* Current tool temperature */
    float temperature;

    /* System humidity */
    float humidity;

    /* Cooling fluid level */
    float fluid_level;
    /* required objects of the system */
    LiquidCrystal_I2C lcd;
    DHT dht;
    WiFiClient esp_client;
    //WiFiClientSecure secure_client;
    PubSubClient client;
    Adafruit_NeoPixel pixels;
    //Stepper motor;
    CheapStepper stepper;
    MFRC522 mfrc522[3];
    byte ssPins[3];
    uint32_t reader_uids[3][NUM_UIDS][4];
    
    bool reader_check[3]; // not used in this code
    //UniversalTelegramBot bot;
    //BlynkTimer blynk_timer;
    
    /* variables used for sending data */ 
    int last_sent, lcd_last; // 
    /*  
        variables usesd to enable/disable wifi,
         mqtt and blnyk connections
    */
    bool mqtt_enabled, wifi_enabled, blynk_enabled;

    /* functions for reading of the main values */
    void read_dht();
    void read_fluid_lvl();
    void verbose_values();

    /*----------------------| Getter |-----------------------*/
    String get_ssid();
    String get_blynk_auth();
    float get_temperature();
    float get_humidity();
    float get_fluid_level();

    /*------------| WiFi/MQTT/Blynk operations |-------------*/
    void publish_data();
    void publish_data(float value1, float value2, float value3);
    void reconnect();
    void blynk_send_data();

    /* ============== | Stepper operations | ================ */

    // --------------| Motor Angle Function | --------------
    void update_position(int angle);
    float get_angle();
    void move_to_op(Operation op);

    /* ----------- | RFID Reader Operations | -------------- */

    void dump_byte_array(byte *buffer, byte bufferSize); // not used in this code
    void reader_loop(); 
    bool is_right_tool(uint8_t reader);


public:
    /*------------| Constructors/Deconstructors |------------*/
    IoTSystem(
            char *ssid,
            char *pwd,
            char *blynk_auth
    );
    ~IoTSystem() {}
    // --------------- | Motor Programms | ------------------

    /* functions for each of the system programs */
    void tool_prog_1();
    void tool_prog_2();
    void tool_prog_3();            


    /*-----------------| Setup procedures |------------------*/
    void setup_wifi();
    void setup_pins();
    void setup_mqtt();
    void setup_blynk();
    void setup_lcd();
    void setup_sensors();
    void setup_reader();
    void setup_speed();

    /* ------------ | Setup NeoPixel RGB Strip | ----------- */
    void setup_neopixel();
    /* ------------------- | Alarm lights | --------------- */
    void setup_blinking_rgb();
    /* ==== | warehouse & changer lights | ===== */
    void setup_rgb_lights();

    /*--------------------| Iot loops |---------------------*/
    void sensor_loop();
    void loop();
};
/* 
is necessary to reach the class IoTSystem from the main.cpp
*/
extern IoTSystem iot;
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
#include <Stepper.h>
#include "config.h"



#define READER_1    0
#define READER_2    1
#define READER_3    2

/**
 * Operation area of the system
 *
 * `IDLE` - System is on hold
 * `OPERATING` - System is in the working area
 * `COOLING` - System is in the cooling state
 * [...]
 */
typedef enum {
    IDLE,
    WORKING,
    COOLING,
    TOOL1,
    TOOL2,
    TOOL3,
} Operation;

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

    LiquidCrystal_I2C lcd;
    DHT dht;
    WiFiClient esp_client;
    PubSubClient client;
    Adafruit_NeoPixel pixels;
    Stepper motor;
    MFRC522 mfrc522[3];
    byte ssPins[3];
    uint32_t reader_uids[3][NUM_UIDS][4] = {
        READER_0_UIDS,  // all rfid tags for reader 0
        READER_1_UIDS,  // all rfid tags for reader 1
        READER_2_UIDS   // all rfid tags for reader 2
    };
    bool reader_check[3];

   //BlynkTimer blynk_timer;
    
    int last_sent, lcd_last;

    void start_cooling();   // not used yet
    void stop_cooling();    // not used yet

    void read_dht();
    void read_fluid_lvl();
    void verbose_values();
    //void stepper_move_angle(float angle);


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
    //void callback(char* topic, byte* payload, unsigned int length);

    /* ============== | Stepper operations | ================ */

    // --------------| Motor Angle Function | --------------
    void moving(int ANGLE);
    void move_to_op(Operation op);

    // --------------- | Motor Programms | ------------------
    void tool_prog_1();
    void tool_prog_2();
    void tool_prog_3();            

    /* ----------- | RFID Reader Operations | -------------- */

    void dump_byte_array(byte *buffer, byte bufferSize);
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
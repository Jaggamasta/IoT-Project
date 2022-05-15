// Copyright (C) <2022> by [Jaggamasta]
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

/**
 * Operation area of the system
 *
 * `IDLE` - System is on hold
 * `OPERATING` - System is in the working area
 * `COOLING` - System is in the cooling state
 * [...]
 */
typedef enum {
    IDLE = 0,
    OPERATING = 1,
    COOLING = 2,
    // [...]
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
   //BlynkTimer blynk_timer;
    
    int last_sent, lcd_last;

    void start_cooling();
    void stop_cooling();

    void read_dht();
    void read_fluid_lvl();
    void verbose_values();
    //void stepper_move_angle(float angle);

    /* ------------------- | Alarm lights | --------------- */
    void setup_blinking_rgb();
    /* ==== | warehouse & changer lights | ===== */
    void setup_rgb_lights();

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

    /*----------------| Stepper operations |-----------------*/

    // --------------| Motor Angle Function | --------------
    void setup_speed();
    void moving(int ANGLE);

    // --------------- | Motor Programms | ------------------
    void motor_prog_1();
    void motor_prog_2();
    void motor_prog_3();            

    /* ----------- | RFID Reader Operations | -------------- */
    void rfid_read();

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

    /* ------------ | Setup NeoPixel RGB Strip | ----------- */
    void setup_neopixel();




    /*--------------------| Super loop |---------------------*/
    void loop();
};



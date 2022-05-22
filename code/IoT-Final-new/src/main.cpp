// Copyright (C) <2022> by IoT-Project-Team-12-DHBW-Stuttgart-TWIE19B

#include <Arduino.h>
#include "system.h"
#include "config.h"

void setup() {
    Serial.begin(115200);
    iot.setup_pins();
    iot.setup_neopixel();
    iot.setup_lcd();
    iot.setup_sensors();
    iot.setup_wifi();
    iot.setup_mqtt();
    iot.setup_blynk();
    iot.setup_speed();
    iot.setup_reader();
}

void loop() {
    iot.loop();
}

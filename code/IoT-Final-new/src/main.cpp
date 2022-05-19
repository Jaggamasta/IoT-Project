// Copyright (C) <2022> by ...
#include <Arduino.h>
#include "system.h"
#include "config.h"

IoTSystem iot(SSID, PASS, AUTH);

void setup() {
    Serial.begin(115200);
    iot.setup_pins();
    iot.setup_neopixel();
    iot.setup_reader();
    iot.setup_lcd();
    iot.setup_sensors();
    iot.setup_wifi();
    iot.setup_mqtt();
    iot.setup_blynk();
}

void loop() {
    iot.loop();
}

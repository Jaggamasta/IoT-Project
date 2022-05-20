#include <Arduino.h>
#include "setup.h"
#include "config.h"

void setup() {

    speed_setup();
}

void loop() {
    
    motor_prog_1();
    //motor_prog_2();
    //motor_prog_3();
}
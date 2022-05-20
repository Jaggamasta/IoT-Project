#include <Arduino.h>
#include <Stepper.h>
#include "config.h"
#include "setup.h"

/* == | Declaration of the Motor Class | == */
Stepper Motor(
    SPU, 
    IN1, 
    IN3, 
    IN2, 
    IN4
    );

// int position = 0;

void speed_setup() {
    Motor.setSpeed(5);
}


/*
Setting up the anlge function
360 degrees /2048 steps = 0.18 factor per degree
*/
void moving(int ANGLE) {
    Motor.step(ANGLE/0.18);         
}

/* 
Motor programm 1
Tool selection order  1 -> 2 -> 3
*/
void motor_prog_1() {
    //Motor.step(SPU);
    moving(210);
    delay(DELAY_VAL);
    //Motor.step(-SPU);
    moving(-100);
    delay(DELAY_WORK);
    moving(100);
    delay(DELAY_VAL);
    moving(-20);
    delay(DELAY_VAL);
    moving(-80);
    delay(DELAY_WORK);
    moving(80);
    delay(DELAY_VAL);
    moving(-20);
    delay(DELAY_VAL);
    moving(-60);
    delay(DELAY_WORK);
    moving(60);
    delay(DELAY_WORK);
    moving(-170);
    delay(DELAY_VAL);
}

/* 
Motor programm 2
Tool selection order  2 -> 3 -> 1
*/
void motor_prog_2() {
    //Motor.step(SPU);
    moving(190);
    delay(DELAY_VAL);
    //Motor.step(-SPU);
    moving(-80);
    delay(DELAY_WORK);
    moving(80);
    delay(DELAY_VAL);
    moving(-20);
    delay(DELAY_VAL);
    moving(-60);
    delay(DELAY_WORK);
    moving(60);
    delay(DELAY_VAL);
    moving(40);
    delay(DELAY_VAL);
    moving(-100);
    delay(DELAY_WORK);
    moving(100);
    delay(DELAY_VAL);
    moving(-210);
    delay(DELAY_VAL);
}
/* 
Motor programm 2
Tool selection order   3 -> 1 -> 2
*/
void motor_prog_3() {
    //Motor.step(SPU);
    moving(170);
    delay(DELAY_VAL);
    //Motor.step(-SPU);
    moving(-60);
    delay(DELAY_WORK);
    moving(60);
    delay(DELAY_VAL);
    moving(40);
    delay(DELAY_VAL);
    moving(-100);
    delay(DELAY_WORK);
    moving(100);
    delay(DELAY_VAL);
    moving(-20);
    delay(DELAY_VAL);
    moving(-80);
    delay(DELAY_WORK);
    moving(80);
    delay(DELAY_VAL);
    moving(-190);
    delay(DELAY_VAL);
}
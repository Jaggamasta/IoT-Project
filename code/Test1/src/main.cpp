#include <Arduino.h>
#include <Stepper.h>

const int SPU = 2048;
#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 26

int position = 0;

Stepper Motor(SPU, IN1, IN3, IN2, IN4); 

void moving(int angle);

void setup() {
Motor.setSpeed(15);

}

void loop() {
  //Motor.step(SPU);
    moving(-300);
    delay(10000);
    //position = position + 300;
   // moving(-210);
   //delay(2000);
   // position = position - 210;
   //Motor.step(-SPU);
   // moving(100);
    //delay(5000);

  //moving(-100);
  //delay(2000);
  //moving(20);
  //delay(2000);
  //moving(80);
  //delay(5000);
  //moving(-80);
  //delay(2000);
  //moving(20);
  //delay(2000);
  //moving(60);
  //delay(5000);
  //moving(-60);
  //delay(2000);
  //moving(170);
  //delay(2000);

}

void moving(int angle){
    position = position + angle;
    Motor.step(angle/0.18);         // 360/2048= 0.18

}
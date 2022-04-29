#include <Arduino.h>

void setup() {
pinMode(2,OUTPUT);
pinMode(15,OUTPUT);
}

void loop() {
digitalWrite(2,HIGH);
digitalWrite(15,HIGH);
delay(1000);
digitalWrite(2,LOW);
delay(1000);
}
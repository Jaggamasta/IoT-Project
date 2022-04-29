#include <Arduino.h>


int LEDblau = 2;
int LEDgruen = 0;
int LEDrot = 4;

int p = 1000;

void setup() {
pinMode(LEDblau, OUTPUT);
pinMode(LEDgruen, OUTPUT);
pinMode(LEDrot, OUTPUT);
}

void loop() {
digitalWrite(LEDblau,LOW);
}

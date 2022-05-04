#include <Arduino.h>
//#include <HCSR04.h>
#include <HCSR04.h>

// Initialize sensor that uses digital pins 13 and 12.
const byte triggerPin = 13;
const byte echoPin = 12;
float distance, ml;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    distance = distanceSensor.measureDistanceCm();
   // ml = distance*0.02;
    Serial.println(distance);
    
    //Serial.print(" in cm");
    delay(1000);

/*
this case will be resolve with the arduino map() function
all we need is to convert values from cm into ml by handling it

3.1 cm = 100% of the tank volume, so the tank is full
11.25 cm = 0% of the tank volume, so the tank is epmty

maube try another function



*/


}
#include <Arduino.h>
#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
float distance = 0;

/*
HCSR04(trigger, echo, temperature, distance)

trigger     - trigger pin
echo        - echo pin
temperature - ambient temperature, in C
distance    - maximun measuring distance, in cm
*/

HCSR04 ultrasonicSensor(16, 17, 20, 300);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(115200);
    ultrasonicSensor.begin(); //set trigger as output & echo pin as input
    lcd.init();
    lcd.backlight();
}

void loop()
{
  distance = ultrasonicSensor.getDistance();

  if (distance != HCSR04_OUT_OF_RANGE)
  {
    lcd.setCursor(0,0);
    lcd.print("Distance in cm:");
    lcd.setCursor(0,1);
    lcd.print(distance, 1);
   }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Distance in cm:");
    lcd.setCursor(0,1);
    lcd.print("0");
    //delay(50);
    //lcd.clear();
  }
delay(50);                                             //wait 50msec or more, until echo from previous measurement disappears

  }

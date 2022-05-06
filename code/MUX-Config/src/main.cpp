#include <Arduino.h>
#include <CD74HC4067.h>

               // s0 s1 s2 s3
CD74HC4067 my_mux(12, 14, 26, 25);  // create a new CD74HC4067 object with its four control pins

const int g_common_pin = 33; // select a pin to share with the 16 channels of the CD74HC4067

void setup()
{
    pinMode(g_common_pin, OUTPUT); // set the initial mode of the common pin.
	                               // This can be changed in loop() for for each channel.
}

void loop()
{
    digitalWrite(g_common_pin, HIGH);

    for (int i = 0; i < 10; i++) {
        my_mux.channel(i);
        delay(1000);
    }
}
#include "config.h"
// reacall the blinking alarm lights function
void blinking_rgb();

void setup() {

    // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.begin();
    // Turn OFF all pixels ASAP
    pixels.show();
    // Setting up  britghness of the Neopixel strip
    pixels.setBrightness(BRIGHTNESS);
}

void loop() {
    
    /* RGB lights warehouse & changer */
    rgb_lights();

    /* --- Blinking Alarm Lights --- */
    blinking_rgb();
    blinking_rgb();
    blinking_rgb();
    blinking_rgb();
    blinking_rgb();
    delay(DELAYVAL);
}
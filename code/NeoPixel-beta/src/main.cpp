#include "setup.h"
#include "config.h"

// reacall the blinking alarm lights function
//

void setup() {
    setup_neopixel ();
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

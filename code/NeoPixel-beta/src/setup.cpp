#include "config.h"
#include "setup.h"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*============================ | Functions | ==============================*/

/* ======================== | setup rgb strip | ========================== */
void setup_neopixel() {
    // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.begin();
    // Turn OFF all pixels ASAP
    pixels.show();
    // Setting up  britghness of the Neopixel strip
    pixels.setBrightness(BRIGHTNESS);
}


/* = | Setting up required RGBG lights for Tool warehouse & Tool changer | =*/
void rgb_lights() {

    /* ========= | Set All Pixel Colors to 'OFF'| ============*/ 
    pixels.clear();

    /*============= | Tool Warehouse Lights | ================*/
    pixels.setPixelColor(0, pixels.Color(155, 155, 155));
    pixels.fill(pixels.Color(155, 0, 155), 1, 3);
    pixels.fill(pixels.Color(0, 0, 155), 4, 3);
    pixels.fill(pixels.Color(155, 155, 0), 7, 3);
    pixels.show();

    /*=========== | RFID Reader Lights | ===============*/
    pixels.setPixelColor(14, pixels.Color(0, 155, 0));
    pixels.setPixelColor(16, pixels.Color(0, 155, 0));
    pixels.setPixelColor(18, pixels.Color(0, 155, 0));
    pixels.show();
    delay(DELAYVAL); 
    pixels.setPixelColor(14, pixels.Color(155, 64, 10));
    pixels.setPixelColor(16, pixels.Color(155, 64, 10));
    pixels.setPixelColor(18, pixels.Color(155, 64, 10));
    pixels.show();
    delay(DELAYVAL);
    pixels.setPixelColor(14, pixels.Color(155, 0, 0));
    pixels.setPixelColor(16, pixels.Color(155, 0, 0));
    pixels.setPixelColor(18, pixels.Color(155, 0, 0));
    pixels.show();
    delay(DELAYVAL);
    
/* ============ | Turning OFF All Lights | ===========  */

    pixels.clear();
    pixels.show();
    delay(DELAYVAL);
}


/* ========== | ALARM FUNCTION AT OVERHEATING | ========= */
void blinking_rgb() {
    
    /* ===== | truning ON all lights in red | ====== */
    pixels.fill(pixels.Color(255, 0, 0), 0, 10);
    pixels.setPixelColor(14, pixels.Color(255, 0, 0));
    pixels.setPixelColor(16, pixels.Color(255, 0, 0));
    pixels.setPixelColor(18, pixels.Color(255, 0, 0));
    pixels.show();
    delay(500);
    
    /* ========= |turnig off all lights| =============*/
    pixels.clear();
    pixels.show();
    delay(500); 
}


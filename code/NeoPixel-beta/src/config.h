#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Board is connected to the NeoPixels?
#define PIN 2
// How many NeoPixels are attached?
#define NUMPIXELS 32
// Time (in milliseconds) to pause between pixels
#define DELAYVAL 5000 
// definition of the brightness level 0-50
#define BRIGHTNESS 20

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*============================ | Functions | ==============================*/

/* Setting up required RGBG lights for Tool warehouse & Tool changer */
void rgb_lights() {

/* ========= | Set All Pixel Colors to 'OFF'| ============*/ 
    pixels.clear();
    /*=========== | Turning on selected Pixels | =============*/    
    
    /*========== | Tool Warehouse Lights | ==============*/
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



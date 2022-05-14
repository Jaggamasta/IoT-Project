#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Board is connected to the NeoPixels?
#define PIN 2
// How many NeoPixels are attached?
#define NUMPIXELS 20
// Time (in milliseconds) to pause between pixels
#define DELAYVAL 5000 
// definition of the brightness level 0-50
#define BRIGHTNESS 30
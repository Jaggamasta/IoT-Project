#pragma once
/**
 * 
SDA     siehe Code (7, 8, 9)
SCK     GPIO 6
MOSI    GPIO 23
MISO    GPIO 19
RST     GPIO 4
GRND    GROUND
3.3V    3.3V 
 */
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// ----------------------- | rfid readers pins | -------------------------------------------
#define RST_PIN         4   // reset pin       
#define SS_1_PIN        7   // SDA pin reader 1        
#define SS_2_PIN        8   // SDA pin reader 2
#define SS_3_PIN        9   // SDA pin reader 3




/* == | pin definitions | == */

#define SDA 13                //LCD, will be removed after integration
#define SCL 14                //LCD, will be removed after integration

/* = | define reader amount | = */
#define NR_OF_READERS   3

/* === | define output lights | ==== */
// they will be removed after integration
#define G_LED           4
#define R_LED           2


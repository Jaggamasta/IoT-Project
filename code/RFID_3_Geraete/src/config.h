#pragma once
/**
 * 
SDA     siehe Code (5, 0, 14)
SCK     GPIO 18
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
#define SS_1_PIN        5   // SDA pin reader 1 (0)        
#define SS_2_PIN        0  // SDA pin reader 2 (1)
#define SS_3_PIN        14   // SDA pin reader 3 (2)




/* == | pin definitions | == */

#define SDA             21                //LCD, will be removed after integration
#define SCL             22                //LCD, will be removed after integration

/* = | define reader amount | = */
#define NR_OF_READERS   3

/* === | define output lights | ==== */
// they will be removed after integration
#define G_LED           36
#define R_LED           35


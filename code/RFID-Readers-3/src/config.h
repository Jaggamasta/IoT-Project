#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <MFRC522.h>



// ----------------------- | rfid readers pins | -------------------------------------------
#define RST_PIN         4   // reset pin       
#define SS_1_PIN        5   // SDA pin reader 1        
#define SS_2_PIN        0   // SDA pin reader 2
#define SS_3_PIN        14   // SDA pin reader 3

/**  
SDA     GPIO 5, 0, 14    
SCK     GPIO 18
MOSI    GPIO 23
MISO    GPIO 19
RST     GPIO 4
GND     GROUND
3.3V    3.3V 
 */

// --------------------- | define reader amount | ------------------------------------------
#define NR_OF_READERS   3
#define NUM_UIDS        3

// -------------------- | reader uid definitions | -----------------------------------------

#define READER_0_UIDS   {\
    {0xA3, 0x42, 0x68, 0x39},\
    {0xC3, 0x77, 0x4A, 0x39},\
    0\
}\

#define READER_1_UIDS   {\
    {0xE6, 0xBD, 0xC6, 0x24},\
    0,\
    0\
}\

#define READER_2_UIDS   {\
    {0x93, 0x86, 0x9D, 0x39},\
    0,\
    0\
}\

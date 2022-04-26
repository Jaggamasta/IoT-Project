#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

#define SS_PIN 5       // ESP32 pin -> GPIO 5
#define RST_PIN 27     // ESP32 pin -> GPIO 27

MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  
    Serial.begin(9600);
    SPI.begin();           // initialize SPI bus
    rfid.PCD_Init();       // initialize MFRC522 reader

    Serial.print("Tap an RFID/NFC tag in the RFID-RC522 reader");

}

void loop() {

    if(rfid.PICC_IsNewCardPresent()){       // new tag is available 
        if(rfid.PICC_ReadCardSerial()){     // new NUID has been readed
            MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
            Serial.print("RFID/NFC tag type is: ");
            Serial.println(rfid.PICC_GetType(piccType));

            // print UID in Serial Monitor in the hex format
            Serial.print("UID: ");
            for(int i = 0; i < rfid.uid.size; i++){
                Serial.print(rfid.uid.uidByte[i] <0x10 ? " 0" : " ");
                Serial.print(rfid.uid.uidByte[i], HEX);

            }
            Serial.println();

            rfid.PICC_HaltA();         // halt PICC
            rfid.PCD_StopCrypto1();    // stop encryption on PCD

        }
    }
}
#include "config.h"
#include "setup.h"

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN};

//zulässige IDs an den Reader (0,1,2)
byte uid_reader_00[] = {0xA3, 0x42, 0x68, 0x39};
byte uid_reader_01[] = {0xC3, 0x77, 0x4A, 0x39};
byte uid_reader_10[] = {0xE6, 0xBD, 0xC6, 0x24};
byte uid_reader_20[] = {0x93, 0x86, 0x9D, 0x39};

int r_0_check = false;
int r_1_check = false;
int r_2_check = false;

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

LiquidCrystal_I2C lcd(0x27, 16,2);  //LCD Instanz

void reader_loop() {

    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

        if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
            Serial.print(F("Reader "));
            Serial.print(reader);
            // Show some details of the PICC (that is: the tag/card)
            Serial.print(F(": Card UID:"));
            dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
            Serial.println();
            Serial.print(F("PICC type: "));
            MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
            Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));


            if (reader == 0){           //prüft ob Reader 0 aktiv ist
                r_0_check = true;
                for (int j=0; j<4; j++){
                if (mfrc522[reader].uid.uidByte[j] != uid_reader_00[j]) {  //Vergleich mit zugewiesen IDs
                    r_0_check = false;
                }
                }
            }

            if (reader == 1){           //prüft ob Reader 1 aktiv ist
                r_1_check = true;
                for (int j=0; j<4; j++){
                if (mfrc522[reader].uid.uidByte[j] != uid_reader_10[j]) {
                    r_1_check = false;
                }
                }
            }

            if (reader == 2){           //prüft ob Reader 2 aktiv ist
            r_2_check = true;
                for (int j=0; j<4; j++){
                if (mfrc522[reader].uid.uidByte[j] != uid_reader_20[j]) {
                    r_2_check = false;
                }
                }
                
            }

            if (r_0_check || r_1_check || r_2_check) {        //prüft ob ein reader das richtige Werkzeug hat
                //digitalWrite(G_LED,HIGH);                       // LED, muss noch durch RGB ersetzt werden
                lcd.print("Richtiges Tool!");
                lcd.setCursor(0,1);
                lcd.print("UID:");
                for (byte i = 0; i < mfrc522[reader].uid.size; i++) {
                lcd.print(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " ");
                lcd.print(mfrc522[reader].uid.uidByte[i], HEX);
                }
            }

            else {                                            //Ablauf für falsches Werkezug
               // digitalWrite(R_LED,HIGH);                       //LED muss noch durch RGN ersetzt werden
                lcd.print("Falsches Tool!");
                lcd.setCursor(0,1);
                lcd.print("UID:");
                for (byte i = 0; i < mfrc522[reader].uid.size; i++){
                lcd.print(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " ");
                lcd.print(mfrc522[reader].uid.uidByte[i], HEX);
                }
            }

            // Halt PICC
            mfrc522[reader].PICC_HaltA();
            // Stop encryption on PCD
            mfrc522[reader].PCD_StopCrypto1();
            delay(2000);
            lcd.clear();
            r_0_check = false;                  //Wird nicht zurückgesetzt... muss nochmal geprüft werden
            r_1_check = false;
            r_2_check = false;
           // digitalWrite(G_LED,LOW);
            //digitalWrite(R_LED,LOW);
            } //if (mfrc522[reader].PICC_IsNewC
    } //for(uint8_t reader    

}


void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setup_lcd() {
    //LCD
    Wire.begin (SDA, SCL);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);

}

void setup_led() {

    pinMode (G_LED, OUTPUT);
    pinMode (R_LED, OUTPUT);
}

void setup_serial() {

    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
}

void setup_reader() {

    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
        
        mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
        Serial.print(F("Reader "));
        Serial.print(reader);
        Serial.print(F(": "));
        mfrc522[reader].PCD_DumpVersionToSerial();
        delay(200);
    }
}
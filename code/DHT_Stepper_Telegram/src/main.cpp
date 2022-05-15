#include <Stepper.h>

#include <Arduino.h>

#include <WiFiClientSecure.h>

#include <UniversalTelegramBot.h>

#include "DHT.h"

#define DHTPIN 4

#define DHTTYPE DHT22   // DHT 11

#define CHAT_ID "5322404568" 
DHT dht(DHTPIN, DHTTYPE);


const int SPU = 2048;
#define IN1 32
#define IN2 33
#define IN3 25
#define IN4 26
#define DHTpin 4 //D15 of ESP32 DevKit
Stepper Motor(SPU, IN1, IN3, IN2, IN4); 
void moving(int angle);
int position = 0;

// Initialize Wifi connection to the router

char ssid[] = "FRITZ!Box 7530 WD";     // Wifi Name

char password[] = "23608700279708193829"; // Wifi Password

// Initialize Telegram BOT

#define BOTtoken "5301428123:AAHCzp-r4Yk1CMvHCgbUsj8PBYd0vLNUwGU" // Bot token from telegram app

WiFiClientSecure client;

UniversalTelegramBot bot(BOTtoken, client);

//Checks for new messages every 1 second.

int botRequestDelay = 100;

unsigned long lastTimeBotRan;

void setup() {
Motor.setSpeed(15);
Serial.begin(9600);
dht.begin();

// This is the simplest way of getting this working

// if you are passing sensitive information, or controlling

// something important, please either use certStore or at

// least client.setFingerPrint

client.setInsecure();

// Set WiFi to station mode and disconnect from an AP if it was Previously

// connected

WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(100);

// attempt to connect to Wifi network:
Serial.print("Connecting Wifi: ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);

}

Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

}

void loop() {

//Motor.step(SPU);
moving(-270); // von Referenzposition in Werkzeuglager
delay(10000);
//Motor.step(-SPU);
moving(90); //Arbeitsposition
delay(5000);
    
int t = dht.readTemperature();
int h = dht.readHumidity();

// in der Arbeitsposition wird überprüft, ob das Werkzeug überhitzt
float temperature = dht.readTemperature();
if (temperature  > 25) { 
    int t = dht.readTemperature();
    String temp = "Digga mir ist warm, mach mal Klima an: ";
    temp += int(t);
    temp +=" *C\n";

    bot.sendMessage(CHAT_ID,temp, "");
    delay(5000);
    moving(90); //Kühlposition
    delay(5000);

// in der Arbeitsposition wird erneut überprüft, ob das Werkzeug überhitzt
    float temperature = dht.readTemperature();
    if (temperature  > 25) { 
        int t = dht.readTemperature();
        String temp = "KOLLEGE IMMERNOCH, MACH MAL WAS ";
        temp += int(t);
        temp +=" *C\n";
        bot.sendMessage(CHAT_ID,temp, "");
        delay(5000);

// in der Arbeitsposition wird erneut überprüft, ob das Werkzeug überhitzt
        float temperature = dht.readTemperature();
            if (temperature  > 25) {

                int t = dht.readTemperature();
                String temp = "IDIOT ICH MACH JETZT EINFACH WEITER UND WENN DIE BUDE ABFACKELT...";
                temp += int(t);
                temp +=" *C\n";
                bot.sendMessage(CHAT_ID,temp, "");
                delay(5000);
                moving(-90); //Arbeitsposition
                delay(5000);


}
}
}
//Werkzeug bewegt sich nach es sich Abschluss der ARbeit wieder auf Ausgangsposition
moving(180);
delay(2000);

lastTimeBotRan = millis();

}
void moving(int angle){
    position = position + angle;
    Motor.step(angle/0.18);         // 360/2048= 0.18

}
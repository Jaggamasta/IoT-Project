#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPLJeVUa6Et"
#define BLYNK_DEVICE_NAME "LEDTEST"
#define BLYNK_AUTH_TOKEN "DFbZQESy7dKSIorVBUb2OEVrtjm4AcL-"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone ";
char pass[] = "12qwasyx";

#define LED01 23
#define LED02 22
#define LED03 21
#define LED04 19
#define LED05 18
#define LED06 5
#define LED07 4
#define LED08 0
#define LED09 2
#define LED10 15

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(23, pinValue);
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(0, pinValue);
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(18, pinValue);
}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  digitalWrite(15, pinValue);
}



void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(15, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
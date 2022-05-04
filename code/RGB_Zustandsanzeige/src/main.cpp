#include <Arduino.h>
#include <analogWrite.h>

int LEDblau = 2;
int LEDgruen = 0;
int LEDrot = 4;
int p = 1000;

void gruenleuchten();
void gelbleuchten();
void rotleuchten();

void setup()
{
pinMode(LEDblau, OUTPUT);
pinMode(LEDgruen, OUTPUT);
pinMode(LEDrot, OUTPUT);
analogWrite(LEDgruen,255); //erstmal alle Farben ausschalten
analogWrite(LEDrot,255);
analogWrite(LEDblau,255);
}

void loop() //Mainschleife, hier können die Funktionen je nach Status abgerufen werden
{
    
gruenleuchten();
delay(p);
gelbleuchten();
delay(p);
rotleuchten();
delay(p);

}

void gruenleuchten()  //Funktion für grünes Licht
{
   
analogWrite(LEDrot, 255);
analogWrite(LEDblau,255);
analogWrite(LEDgruen,0);  

}

void gelbleuchten() //Funktion für gelbes Licht
{
analogWrite(LEDrot, 0);
analogWrite(LEDblau,255);
analogWrite(LEDgruen,0); 
}

void rotleuchten() //Funktion für rotes Licht
{
analogWrite(LEDrot, 0);
analogWrite(LEDblau,255);
analogWrite(LEDgruen,255); 
}
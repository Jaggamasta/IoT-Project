#include <Arduino.h>
#include <CD74HC4067.h>
//16-Channel MUX (74HC4067) Interface
//===================================
int Signal = 5; int i; int SW = 4;
int pot = A0; int potVal; int S[4] = {9,8,7,6};
int MUXtable[16][4]=
{
  {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {1,1,0,0},
  {0,0,1,0}, {1,0,1,0}, {0,1,1,0}, {1,1,1,0},
  {0,0,0,1}, {1,0,0,1}, {0,1,0,1}, {1,1,0,1},
  {0,0,1,1}, {1,0,1,1}, {0,1,1,1}, {1,1,1,1}
};
//=================================================
void setup()
{
  pinMode(Signal,OUTPUT);
  for(i=0; i<4; i++) pinMode(S[i],OUTPUT);
}
//=================================================
void loop()
{
  for(i=0; i<10; i++)
  {
    selection(i);
    potVal = map(analogRead(pot),0,1023,20,400);
    if(digitalRead(SW)==HIGH) break;
    digitalWrite(Signal,HIGH); delay(potVal);
    digitalWrite(Signal,LOW); delay(potVal);
  }
}
//=================================================
void selection(int j)
{
  digitalWrite(S[0], MUXtable[j][0]);
  digitalWrite(S[1], MUXtable[j][1]);
  digitalWrite(S[2], MUXtable[j][2]);
  digitalWrite(S[3], MUXtable[j][3]);
}

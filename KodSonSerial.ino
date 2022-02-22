#include <LiquidCrystal.h>
#define soundpin A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sndreading;
int slideswitch = 8;
int S = 00;        // count seconds 
int M = 00;        // count minutes

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(slideswitch, INPUT);
}

void loop() 
{    
  if (digitalRead(slideswitch))
{   
    S=0;
    M=0;
//    Serial.clear();
//    Serial.setCursor(0, 0);
    Serial.print("  Time= 00:00 ");
//    Serial.setCursor(0, 1);
//    Serial.print("System Rebooted");
    delay(2000);
} 
  
 else if (!digitalRead(slideswitch))
{
  
  sndreading = analogRead(soundpin);
  
  if (sndreading < 540)
  {
//  Serial.clear();
//  Serial.setCursor(0, 0);
  Serial.print("ATA Ammo Counter");
//  Serial.setCursor(0, 1);
  Serial.print("Last Time=   :");
//  Serial.setCursor(12, 1);
  Serial.print(M);
//  Serial.setCursor(14, 1);
  Serial.print(S);
  delay(1500);
  }   
  else
  {  
    if (sndreading >= 540) 
    { 
//     Serial.clear();
     
// Serial.setCursor(0, 0); 
 Serial.print (" Timer Started ");
// Serial.setCursor(6, 1);
 Serial.print("0");
// Serial.setCursor(8, 1);
 Serial.print(":");
// Serial.setCursor(7, 1);
 Serial.print(M);
 
 S++;
 delay(1000);
  
 if(S > 59)
 {
  S=0;   
    M = M+1;
//    Serial.setCursor(7, 1);
    Serial.print(M);
//    Serial.setCursor(6, 1);
    Serial.print("0");
 }
 
  if(S > 9)
 {
//    Serial.setCursor(9, 1);
    Serial.print(S);
 }     
      
 else
 {
//   Serial.setCursor(9, 1);
   Serial.print("0"); 
//   Serial.setCursor(10, 1);
   Serial.print(S);
//   Serial.setCursor(11, 1);
   Serial.print(" ");
 }  
      delay(100);
    } 
    
}
}
  delay(100);
}

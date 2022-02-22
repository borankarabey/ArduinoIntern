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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Time= 00:00 ");
    lcd.setCursor(0, 1);
    lcd.print("System Rebooted");
    delay(2000);
} 
  
 else if (!digitalRead(slideswitch))
{
  
  sndreading = analogRead(soundpin);
  
  if (sndreading < 540)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ATA Ammo Counter");
  lcd.setCursor(0, 1);
  lcd.print("Last Time=   :");
  lcd.setCursor(12, 1);
  lcd.print(M);
  lcd.setCursor(14, 1);
  lcd.print(S);
  delay(1500);
  }   
  else
  {  
    if (sndreading >= 540) 
    { 
     lcd.clear();
     
 lcd.setCursor(0, 0); 
 lcd.print (" Timer Started ");
 lcd.setCursor(6, 1);
 lcd.print("0");
 lcd.setCursor(8, 1);
 lcd.print(":");
 lcd.setCursor(7, 1);
 lcd.print(M);
 
 S++;
 delay(1000);
  
 if(S > 59)
 {
  S=0;   
    M = M+1;
    lcd.setCursor(7, 1);
    lcd.print(M);
    lcd.setCursor(6, 1);
    lcd.print("0");
 }
 
  if(S > 9)
 {
    lcd.setCursor(9, 1);
    lcd.print(S);
 }     
      
 else
 {
   lcd.setCursor(9, 1);
   lcd.print("0"); 
   lcd.setCursor(10, 1);
   lcd.print(S);
   lcd.setCursor(11, 1);
   lcd.print(" ");
 }  
      delay(100);
    } 
    
}
}
  delay(100);
}

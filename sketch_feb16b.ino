 #include "LiquidCrystal.h"  

 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
 int irPin = 10;    
 int sideswitch = 8;
 int count = 0;
 int newcount = 0;
 int S = 59;     // count seconds 
 int M = 0;     // count minutes

 boolean state = true; 

 void setup()  
 { 
  Serial.begin(9600);  
  lcd.begin(16, 2);  
  pinMode(irPin, INPUT);  
  pinMode(sideswitch, INPUT);
 } 

 void loop()  
 {
  if (digitalRead(irPin) && state)
  {  
  newcount = count++; 
    state = false;  
    lcd.clear();
    timer();
  } 
   
  else if (!digitalRead(irPin))  
  {  
    state = true;
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("Count No: ");
    lcd.setCursor(0, 1);
    lcd.print("ATA Ammo Counter");
    Serial.print("Count: ");  
    Serial.println(newcount);  
    lcd.setCursor(10, 0);  
    lcd.print(count);
    delay(1000);
  }  
   
  if (digitalRead(sideswitch))
  { 
    count = 0;  
    //state = true;   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count No: 0");
    lcd.setCursor(0, 1);
    lcd.print("System Rebooted");
    delay(2000);
  } 
 }

void timer(){
 
 while(S!=0 && digitalRead(irPin)){ 
 lcd.setCursor(0, 0); 
 lcd.print ("1 Minute Started");
 lcd.setCursor(6, 1);
 lcd.print("00:");
 
 S--;
 delay(1000);
  
 if(S < 0)
 {
   M--;
   S = 59;
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
 }
}

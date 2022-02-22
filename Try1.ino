/*
Ammo Counter Application
Uses Uno, LCD shield and E18-D80NK infrared module to implement
for ammo in a reloading station as it falls into a bucket.
Note that there are some Serial.Println statements sprinked ab
These are simply for debugging purposes.
*/
#include <LiquidCrystal.h>
// Define the pins used by the LCD panel. These are fixed by the
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
///const int BTN_RIGHT = 0;
const int BTN_UP = 0;
const int BTN_DOWN = 1;
///const int BTN_LEFT = 3;
const int BTN_SELECT = 4;
const int BTN_NONE = 3;
const int BACKLIGHT_PIN = 10;
const int OFF = 0;
const int ON = 1;
int lcd_key = BTN_NONE;
int adc_key_in = 0;
int backlight_state = ON;
int tone_on = ON;

int TonePin = 12; // Pin connected to Passive Buzzer XXX /// Pin connected to Pulb
//int Freq = 200; // Frequency to play buzzer at
unsigned int counter = 0; // Holds the current count
unsigned int old_count = 0; // Holds last count displayed
//===============================================================
// Initialization
//===============================================================
void setup() {
pinMode(TonePin, OUTPUT);
Serial.begin(9600);

lcd.begin(16, 2); // Initialize LCD for 16 charact
lcd.setCursor(0, 0); // Position cursor to 1st col, 1
lcd.print("ATA Ammo Counter"); // print a message on the 1st li
lcd.setCursor(0, 1); // Position cursor 1st col, 2nd l
lcd.print("Count: "); // Print 'Count'
lcd.setCursor(15, 1); // Position cursor 15th col, 2nd
lcd.print("L"); // Print 'B' as buzzer is ON by d XXX /// Print 'L' as pulb is ON by d
lcd.setCursor(7, 1); // Position cursor to the count l
digitalWrite(BACKLIGHT_PIN, LOW); // We set this pin LOW just o
// to input or output to turn the backlight on/off
attachInterrupt(0, Do_Count, FALLING); // Create interrupt han
// pulses on falling edge of Int0 as sensor goes LOW when objec
}
//===============================================================
// Main
//===============================================================
void loop() {
if (counter > old_count) { // Check the counter variable to
Update_Count(); // handler incremented it. If so
}
lcd_key = Read_Buttons(); // read the buttons
if (lcd_key != BTN_NONE) Do_Buttons(); // If a button is press
}
//===============================================================
// Subroutine - Increments the ammo counter when interrupt pin g
//===============================================================
void Do_Count()
{
counter++; // increment of the counter value
}
//===============================================================
// Subroutine - Updates the count on the display
//===============================================================
void Update_Count()
{
Serial.println (counter);
lcd.setCursor(7, 1);
lcd.print(" "); // Clear current count space
lcd.setCursor(7, 1);
lcd.print(counter); // Print new count
old_count = counter; // Set the old_count to our new count
if (tone_on == ON) tone(TonePin, Freq, 300); // If buzzer on,
}
//===============================================================
// Read Buttons - Subroutine to read the ADC and return the butt
//===============================================================
int Read_Buttons()
{
adc_key_in = analogRead(0); // read analog value from the
// The buttons are connected to voltage divider that feeds into
// By looking at the voltage level, we can tell which button ha
// With no button pressed, the voltage will be pulled up to Vcc
if (adc_key_in >= 1000) return BTN_NONE; // Most likely result,
///if (adc_key_in < 50) return BTN_RIGHT; // Work our way up the
if (adc_key_in < 195) return BTN_UP; // And return first va
if (adc_key_in < 380) return BTN_DOWN;
///if (adc_key_in < 555) return BTN_LEFT;
if (adc_key_in < 790) return BTN_SELECT;
return BTN_NONE; // when all others fail, return this...
}
//===============================================================
// Do Buttons - Subroutine to act on the button pushes
//===============================================================
int Do_Buttons()
/*
* Note that we are using a delay(500) on the buttons to debounce
* Since the buttons probably aren't going to be pushed while als
* reloading machine, we don't expect this hard delay to cause an
*/
{
switch (lcd_key)
{
case BTN_RIGHT: // Turns buzzer ON/OFF and sets a 'B' if it XXX // Turns pulb ON/OFF and sets a 'L' if it
{
tone_on = (tone_on == ON) ? OFF : ON;
Serial.println(tone_on);
if (tone_on == ON) {
lcd.setCursor(15, 1);
lcd.print("L");
}
else {
lcd.setCursor(15, 1);
lcd.print(" ");
}
delay(500); // Button debounce delay
break;
}
///case BTN_LEFT: // Sets counter to zero
///{
///counter = 0;
///Update_Count();
///delay(500); // Button debounce delay
///break;
///}
case BTN_UP: // Increments counter
{
counter++;
Update_Count();
delay(500); // Button debounce delay
break;
}
case BTN_DOWN: // Decrements counter
{
if (counter > 0) {
counter--;
Update_Count();
delay(500); // Button debounce delay
}
break;
}
case BTN_SELECT: // Toggles backlight ON / OFF
{
if (backlight_state == ON) {
pinMode(BACKLIGHT_PIN, OUTPUT);
backlight_state = OFF;
}
else if (backlight_state == OFF) {
pinMode(BACKLIGHT_PIN, INPUT);
backlight_state = ON;
}
delay(500); // Button debounce delay
break;
}
case BTN_NONE:
{
break;
}
}
}

#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogReading = analogRead(FORCE_SENSOR_PIN);

  Serial.print("Force sensor reading = ");
  Serial.print(analogReading);

  if (analogReading < 10)       
    Serial.println(" -> no pressure");
  else if (analogReading < 100) 
    Serial.println(" -> light touch");
  else if (analogReading < 200) 
    Serial.println(" -> light squeeze");
  else if (analogReading < 300) 
    Serial.println(" -> medium squeeze");
  else
    Serial.println(" -> big squeeze");

  delay(1000);
}

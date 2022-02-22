
const int shotPin = 7;
const int sample_time = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

// Time Variables
unsigned long start_measure = 0;
unsigned long end_measure = 0;
unsigned long duration = 0;

int buffer = 0;
int mybuffer = 0;

bool flag_on = 0;


void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(shotPin, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(shotPin) == LOW)
  {
    buffer ++;
  }

  if(millisElapsed > sample_time) 
  {
    //Serial.println(buffer);
    mybuffer = buffer;
    buffer=0;
    millisLast = millisCurrent;
  }
  if(mybuffer > 150)// burda istedigin sesi ayarla
  {
    start_measure = millis();
    flag_on = 1;
  }
  if (flag_on == 1)
  {
    if(mybuffer <150)
    {
      end_measure = millis();
      duration = end_measure - start_measure; 
      flag_on = 0;
      Serial.println(duration); 
    } 
  }
  
  
  
}

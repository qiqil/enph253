/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h>   

void setup()
{
    #include <phys253setup.txt>
    Serial.begin(9600);  
}

bool value;
unsigned long count;

void loop(){
  count = 0;
  unsigned long startTime = micros();
  unsigned long endtime = startTime;
  value = digitalRead(0);
  bool newValue;
  while ((endtime - startTime) <= 1000000)
  {
    newValue = digitalRead(0);
    if(newValue!=value)
    {
      count++;
      value = newValue;
    }
    endtime = micros();
  }

  LCD.clear(); LCD.home();
  Serial.print(count/2.0);
}


/*
volatile int count;
void loop(){
  double startTime = millis();
  double endtime = startTime;
  value = digitalRead(0);
  while ((endtime - startTime) <= 200)
}

void count(){
  count++;
}
*/

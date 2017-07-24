/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h> 

ServoTINAH servos[6];

void setup()
{
  portMode(0, INPUT) ;      //   ***** from 253 template file
  portMode(1, OUTPUT) ;      //   ***** from 253 template file
  
  LCD.begin(16,2) ;

  for (int i = 0; i <6; i++)
  {
    servos[i].attach(i+8);
  }
  
  Serial.begin(9600);  
}

void loop()
{
  for (int i = 0; i <6; i++)
  {
    servos[i].write(90);
  }
}

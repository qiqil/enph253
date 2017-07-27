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
 
void loop()
{ 
  LCD.clear(); LCD.home();
  LCD.print("0 - ");
  LCD.print(analogRead(0));
  LCD.print(" 1 - ");
  LCD.print(analogRead(1));
  LCD.setCursor(0,1);
  LCD.print("2 - ");
  LCD.print(analogRead(2));
  LCD.print(" 3 - ");
  LCD.print(analogRead(3));
  delay(200);
}

/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h>    

bool strategyIsSet = false;
int course = 0; //0 = no course, 1 = right, 2 = left
float kp = 30;
float kd = 30;
int threshold = 31;
int gain = 1;
int SPEED = 200;

void setup()
{
    #include <phys253setup.txt>
    Serial.begin(9600);  
}
 
void loop()
{ 
  mainMenu();
//  
//  LCD.clear(); LCD.home();
//  double voltage = analogRead(7);
//  LCD.print(voltage*5/1024);
//  delay(100);
}



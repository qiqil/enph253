/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h>    

bool strategyIsSet = false;
int course = 0; //0 = no course, 1 = right, 2 = left
float kp = 40;
float kd = 50;
int threshold = 40;
int gain = 1;
int SPEED = 200;
int currentSPEED = SPEED;
float rightSensorCorrection = 1;
float rightTotal;
float leftTotal;
float lastIR;
int pastGate = 0;
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
  mainMenu();
//  for (int i = 0; i <6; i++)
//  {
//    servos[i].write(90);
//  }
//  
//  LCD.clear(); LCD.home();
//  double voltage = analogRead(7);
//  LCD.print(voltage*5/1024);
//  delay(100);
}



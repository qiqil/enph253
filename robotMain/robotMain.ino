/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h>
#include <ServoTINAH.h>   

bool strategyIsSet = false;
int course = 0; //0 = no course, 1 = right, 2 = left
float kp = 20; //30
float kd = 35; //40
int threshold = 60; //tape following
int gain = 1;
int SPEED = 170; //200
int currentSPEED = SPEED;
int pastGate = 0;
float tenkhzThresh = 20; //change
float onekhzThresh = 20; //change
ServoTINAH baseServo;

void setup()
{
  portMode(0, INPUT) ;      //   ***** from 253 template file
  portMode(1, OUTPUT) ;      //   ***** from 253 template file
  
  LCD.begin(16,2) ;
  RCServo0.attach(RCServo0Output) ;    // attaching the digital inputs to the RC servo pins on the board.  
  RCServo1.attach(RCServo1Output) ;
  RCServo2.attach(RCServo2Output) ;
  baseServo.attach(8);
  RCServo2.write(0);
  RCServo0.write(0);
  baseServo.write(180);
  RCServo1.write(180);
  delay(500);
  baseServo.write(0);  
  
  Serial.begin(9600);  
}
 
void loop()
{ 
  //pickUpAgentOne();
 
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



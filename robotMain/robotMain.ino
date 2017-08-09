/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h>
#include <ServoTINAH.h>   

bool strategyIsSet = false;
int course = 0; //0 = no course, 1 = right, 2 = left

//tapeFollowing
float kp = 40; //30
float kd = 45; //40
int threshold = 60; //tape following
int gain = 1;
int SPEED = 250; //200
int currentSPEED = SPEED;
int bounceCount = 24;
bool pastGate = false; 
float tenkhzThresh = 20; //change
float onekhzThresh = 20; //change
ServoTINAH baseServo;

volatile unsigned long left_rotations = 0;
volatile unsigned long right_rotations = 0;

ISR(INT0_vect){}
ISR(INT1_vect){right_rotations++;}
ISR(INT2_vect){}
ISR(INT3_vect){left_rotations++;}

void enableExternalInterrupt(unsigned int INTX, unsigned int mode) {
  if (INTX > 3 || mode > 3 || mode == 1) return;
  cli();
  /* Allow pin to trigger interrupts        */
  EIMSK |= (1 << INTX);
  /* Clear the interrupt configuration bits */
  EICRA &= ~(1 << (INTX*2+0));
  EICRA &= ~(1 << (INTX*2+1));
  /* Set new interrupt configuration bits   */
  EICRA |= mode << (INTX*2);
  sei();
}

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
  RCServo1.write(180);
  delay(500);
  baseServo.write(0);  

    stopMotors();
  Serial.begin(9600);

  enableExternalInterrupt(INT0, RISING);
  enableExternalInterrupt(INT1, RISING);
  enableExternalInterrupt(INT2, RISING);
  enableExternalInterrupt(INT3, RISING);
}
 
void loop()
{ 
  //delay(2000);
 
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



/*
 * TINAH Template Program - UBC Engineering Physics 253
 * (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
 */
 
#include <phys253.h>          
#include <LiquidCrystal.h> 
//#include <Servo.h>

void setup() {
     #include <phys253setup.txt>
    Serial.begin(9600); 
  

}

void loop() {

int potval=knob(7);
int potval2=knob(6);

LCD.clear();
LCD.home();
LCD.setCursor(0,0); LCD.print(potval-512);
LCD.print(" ");
//LCD.setCursor(0,1); LCD.print(potval2);

double speed = potval-512;
motor.speed(0,speed);
//double angle = potval/5.7;
//RCServo0.write(angle);  
delay(100);

}

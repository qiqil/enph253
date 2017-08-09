//Encoder Based Movements
const int eKd = 15; //8
const int eKi = 30;
const int integralLimit = 60;
const int stepSize = 1;
const int MAX_SPEED = 255;

void brake(int speed = MAX_SPEED, String dir = "FWD");

void stopMotors (){
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void driveStraight(unsigned long distance, int speed){
  int prevControl = 0;
  int control= 0;
  int devCount = 0;
  int integralControl = 0;

  resetRotations();
  
  while(left_rotations < distance || right_rotations < distance) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(left_rotations);
    LCD.setCursor(7, 0); LCD.print(speed-control);
    LCD.setCursor(0, 1); LCD.print(right_rotations);
    LCD.setCursor(7, 1); LCD.print(speed+control);
 
    control = 0;
    if (left_rotations > right_rotations + stepSize) {
      control = eKi;
//      if (abs(control) >= abs(prevControl)) {integralControl++;}
    } else if (left_rotations < right_rotations - stepSize) {
      control = -eKi;
//      if(abs(control) >= abs(prevControl)) {integralControl--;} 
    }
//
//    if(abs(integralControl) >= integralLimit) {integralControl = integralLimit * integralControl/abs(integralControl);}
//    
//    if (control == prevControl){devCount = 1;}
//    else {devCount++;}
//    
////posterity, incorrect config, donot delete
////    motor.speed(0, speed - control);
////    motor.speed(1, speed + control);

    control += devCount * eKd;
    motor.speed(0, speed + control); // right motor 
    motor.speed(1, speed - control); // left motor

    prevControl = control;
  }

  stopMotors();
}

void reverse(unsigned long distance, int speed){
  
}

//Braking for constant time, write REV if reversing, else leave void
//specify speed unless maxSpeed is desired
void brake(int speed, String dir){
  if (dir.equals("FWD")){
    moveRightMotor(-speed);
    moveLeftMotor(-speed);
    delay(10);
  }
  else if (dir.equals("REV")){
    moveRightMotor(speed);
    moveLeftMotor(speed);
    delay(10);
  }

  stopMotors();
}

//left wheel = 0, right wheel = 1
//+ angle is CW
void rotate(int angle){
  resetRotations();
  stopMotors();

  if (angle == 0) return;

  int revCountMax = 0;

  if (angle > 0) {
    revCountMax = angle/3 +0.5;
    LCD.clear(); LCD.home();
    LCD.print(revCountMax);
    while(abs(left_rotations) <= revCountMax || abs(right_rotations) <= revCountMax){
      moveRightMotor(-MAX_SPEED);
      moveLeftMotor(MAX_SPEED);
    }
  }

  if (angle < 0) {
    revCountMax = angle/3 -0.5;
    revCountMax = abs(revCountMax);
    LCD.clear(); LCD.home();
    LCD.print(revCountMax);
    while(abs(left_rotations) <= revCountMax || abs(right_rotations) <= revCountMax){
      moveRightMotor(MAX_SPEED);
      moveLeftMotor(-MAX_SPEED);
      Serial.println(right_rotations);
      Serial.print(left_rotations);
    }
  }
  
  stopMotors();
}

void resetRotations(){
  left_rotations = 0;
  right_rotations = 0;
}

void moveRightMotor(int speed){
  for(int currSpeed = 0; currSpeed <= speed; currSpeed++){
    motor.speed(0, currSpeed);
    delay(2);
  }

  motor.speed(0, speed);
}

void moveLeftMotor(int speed){
  for(int currSpeed = 0; currSpeed <= speed; currSpeed++){ 
    motor.speed(1, speed);
    delay(2);
  }

  motor.speed(0, speed);
}


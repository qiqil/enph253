// servo0, servo1 - backarm 0 degrees pointing straight up
// servo2 -forearm - 180pointing towards chassis
// motor2 - end effector - 1.8sec to close, when close give it small speed to keep it closed
// digital pin - base - 0 = pointing left facing TINAH
void moveArmToStartPosition()
{
  RCServo2.write(0);
  baseServo.write(80);
  delay(300);
  RCServo0.write(100);
  RCServo1.write(180-100);
}
//------------------------------------------------------------------------
void pickUpAgentOne() {
  // medium position
  int backarmAngle = 0;
  backArmPosition(backarmAngle, 2); //2nd param is delay time, moving servo (bigger means slower movement)
  delay(500);
  foreArmPosition(0,2); //second parameter is always the delay time (ms), moving servo
  motor.speed(2, -255);
  delay(2000);
  motor.speed(2, 0);
  
  positionAndGrab(2);
  liftAndDropIntoBin();
}

void pickUpAgentTwo() {
  //lower claw to lowest position
  positionAndGrab(1);
  liftAndDropIntoBin();
}

void pickUpAgentThree() {
  //lower claw to highest position
  positionAndGrab(3);
  liftAndDropIntoBin();
}

void pickUpAgentFour() {
  //lower claw to medium position
  positionAndGrab(2);
  liftAndDropIntoBin();
}

void pickUpAgentFive() {
  //lower claw to lowest position
  positionAndGrab(1);
  liftAndDropIntoBin();
}

void pickUpAgentSix() {
  //lower claw to highest position
  positionAndGrab(3);
  liftAndDropIntoBin();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void positionAndGrab(int position) { // 1 to 3, 1 lowest 3 highest
  if (course == 0 || course == 1) {
    baseServoPosition(20, 5);
  }
  else {
    baseServoPosition(180, 5);
  }
  delay(300);

  int backarmAngle = 0;
  int forearmAngle = 0; //change 
  if (position == 1) backarmAngle = 130; forearmAngle = 40; //change 
  if (position == 2) backarmAngle = 130; forearmAngle = 40; // change
  if (position == 3) backarmAngle = 130; forearmAngle = 40;// change

  backArmForeArmPosition(backarmAngle, forearmAngle, 5); //move both same time, delay time of 5 ms
  
  delay(500);
  motor.speed(2, 255);
  delay(2500);
  motor.speed(2,50);
}
//------------------------------------------------------------------------------------------------------------------
void baseServoPosition(int baseAngle, int delayTime) { //delayTime is how slow we want it to move
  for(int angle = 0; angle <= baseAngle; angle++) { 
    baseServo.write(angle);
    delay(delayTime);
  }
}

void foreArmPosition( int foreArmAngle, int delayTime) {
  for(int angle = 0; angle <=foreArmAngle; angle++) {
    if(angle > foreArmAngle) RCServo2.write(180+foreArmAngle-angle);
    delay(delayTime);
  }
}

void backArmPosition(int backArmAngle, int delayTime) {
  for (int angle = 0; angle <=backArmAngle; angle++) {
    RCServo0.write(angle);
    RCServo1.write(180-angle);
    delay(delayTime);
  }
}

void backArmForeArmPosition( int backArmAngle, int foreArmAngle,int delayTime) {  //moving both forearm and back arm same time
  for(int angle = 0; angle <=backArmAngle; angle++) {
    RCServo0.write(angle);
    RCServo1.write(180-angle);
    if(angle > foreArmAngle) RCServo2.write(180+foreArmAngle-angle);
    delay(delayTime);
  }
}


void liftAndDropIntoBin()
{
  int backarmAngle = 0;
  backArmPosition(backarmAngle, 5);
  delay(1000);
  foreArmPosition(180, 5);
  baseServoPosition(90, 5);
  delay(500);
  motor.speed(2, -255);
  delay(2500);
  motor.speed(2, 0);
}

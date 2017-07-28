// servo0, servo1 - backarm
// servo2 -forearm - 180pointing towards chassis
// motor2 - end effector - 1.8sec to close, when close give it small speed to keep it closed
// digital pin - base - 0 = pointing left facing TINAH

void pickUpAgentOne() {
  // medium position
  int backarmAngle = 0;
  RCServo0.write(backarmAngle);
  RCServo1.write(180-backarmAngle);
  delay(500);
  RCServo2.write(0);
  
  if (course == 0 || course == 1)
  {
    baseServo.write(0);
  }
  else
  {
    baseServo.write(180);
  }
  delay(300);
  int backarmAngle = 150; //0 degrees = pointing straight up
  int forearmAngle = 80;
  for (int angle = 0; angle <= backarmAngle; angle++)
  {
    RCServo0.write(angle);
    RCServo1.write(180-angle);
    if(angle <= forearmAngle)
    {
      RCServo2.write(angle);
    }
    delay(10);
  }
  delay(500);
  motor.speed(2, 200);
  delay(4000);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentTwo() {
  //lower claw to lowest position
  if (course == 0 || course == 1)
  {
    baseServo.write(0);
  }
  else
  {
    baseServo.write(180);
  }
  delay(300);
  int backarmAngle = 150; //0 degrees = pointing straight up
  int forearmAngle = 80;
  for (int angle = 0; angle <= backarmAngle; angle++)
  {
    RCServo0.write(angle);
    RCServo1.write(180-angle);
    if(angle <= forearmAngle)
    {
      RCServo2.write(angle);
    }
    delay(10);
  }
  delay(500);
  motor.speed(2, 200);
  delay(4000);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentThree() {
  //lower claw to highest position
}

void pickUpAgentFour() {
  //lower claw to medium position
}

void pickUpAgentFive() {
  //lower claw to lowest position
}

void pickUpAgentSix() {
  //lower claw to highest position
}

void liftAndDropIntoBin()
{
  int backarmAngle = 0;
  RCServo0.write(backarmAngle);
  RCServo1.write(180-backarmAngle);
  delay(1000);
  RCServo2.write(180);
  baseServo.write(90);
  delay(500);
  motor.speed(2, -200);
  delay(3000);
  motor.speed(2, 0);
}



// servo0, servo1 - backarm 0 degrees pointing straight up
// servo2 -forearm - 180pointing towards chassis
// motor2 - end effector - 1.8sec to close, when close give it small speed to keep it closed
// digital pin - base - 0 = pointing left facing TINAH
int backarmRestAngle = 90;
int baseRestAngle = 104;
int rightCourseBasePickupAngle = 10;
int leftCourseBasePickupAngle = 170;
int closeTime = 3800;
int openTime = 3800;
float backarmGrabAngle = 90;
float forearmGrabAngle = 130;
float backarmZiplineGrabAngle = 60;
float forearmZiplineGrabAngle = 120;

void moveArmToStartPosition()
{
  RCServo2.write(0);
  baseServo.write(80);
  delay(300);
  RCServo0.write(100);
  RCServo1.write(180-100);
}

void grabZiplineMechanismAndLift()
{
    moveBackarmAtSpeed(0, 5);
    moveBaseAtSpeed(120, 10);
    moveForearmAtSpeed(0, 5);

    for (int angle = 0; angle < backarmZiplineGrabAngle; angle++)
    {
      moveBackarmAtSpeed(angle, 5);
      float factor = (forearmZiplineGrabAngle)/backarmZiplineGrabAngle;
      moveForearmAtSpeed(angle*factor, 5); //forearmstarts at 180
    }

    motor.speed(2, 255);
    delay(closeTime);
    motor.speed(2, 50);
  
    moveBackarmAtSpeed(0, 5);
    moveBaseAtSpeed(100, 10);
    moveForearmAtSpeed(0, 5);
}
//------------------------------------------------------------------------
void pickUpAgentOne() {
  // medium position
  moveBackarmAtSpeed(0, 5);
  moveForearmAtSpeed(180, 5);
//  motor.speed(2, -255);
//  delay(2000);
//  motor.speed(2, 0);
  
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = (180-forearmGrabAngle)/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentTwo() {
  //lower claw to lowest position
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = forearmGrabAngle/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentThree() {
  //lower claw to highest position
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = forearmGrabAngle/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentFour() {
  //lower claw to medium position
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = forearmGrabAngle/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentFive() {
  //lower claw to lowest position
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = forearmGrabAngle/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void pickUpAgentSix() {
  //lower claw to highest position
  if (course == 0 || course == 1)
  {
    moveBaseAtSpeed(rightCourseBasePickupAngle, 5);
  }
  else
  {
    moveBaseAtSpeed(leftCourseBasePickupAngle, 5);
  }
  delay(200);

  for (int angle = 0; angle < backarmGrabAngle; angle++)
  {
    moveBackarmAtSpeed(angle, 5);
    float factor = forearmGrabAngle/backarmGrabAngle;
    moveForearmAtSpeed(180 - angle*factor, 5); //forearmstarts at 180
  }

  motor.speed(2, 255);
  delay(closeTime);
  motor.speed(2, 50);
  liftAndDropIntoBin();
}

void liftAndDropIntoBin()
{
  moveBackarmAtSpeed(0, 8);
  moveForearmAtSpeed(180, 5);
  moveBaseAtSpeed(100, 20);
  
  motor.speed(2, -255);
  delay(openTime);
  motor.speed(2, 0);
}

void moveForearmAtSpeed(int angle, int delayTime)
{
  int startAngle = RCServo2.read();
  if(startAngle < angle)
  {
    for (int currentAngle = startAngle; currentAngle < angle; currentAngle++)
    {
      RCServo2.write(currentAngle);
      delay(delayTime);
    }
  }
  else {
    for (int currentAngle = startAngle; currentAngle > angle; currentAngle--)
    {
      RCServo2.write(currentAngle);
      delay(delayTime);
    }
  }
}

void moveBackarmAtSpeed(int angle, int delayTime)
{
  int startAngle = RCServo0.read();
  if(startAngle < angle)
  {
    for (int currentAngle = startAngle; currentAngle < angle; currentAngle++)
    {
      RCServo0.write(currentAngle);
      RCServo1.write(180-currentAngle);
      delay(delayTime);
    }
  }
  else {
    for (int currentAngle = startAngle; currentAngle > angle; currentAngle--)
    {
      RCServo0.write(currentAngle);
      RCServo1.write(180-currentAngle);
      delay(delayTime);
    }
  }
}

void moveBaseAtSpeed(int angle, int delayTime)
{
  int startAngle = baseServo.read();
  if(startAngle < angle)
  {
    for (int currentAngle = startAngle; currentAngle < angle; currentAngle++)
    {
      baseServo.write(currentAngle);
      delay(delayTime);
    }
  }
  else {
    for (int currentAngle = startAngle; currentAngle > angle; currentAngle--)
    {
      baseServo.write(currentAngle);
      delay(delayTime);
    }
  }
}


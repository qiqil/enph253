float irSensor1 = 0;
float irSensor10 = 0;

void runCourse()
{
  pastGate = 0;
  resetRotations();
  LCD.clear(); LCD.home();
  LCD.print("Tape Following");
  moveArmToStartPosition();
  delay(1000); 
  tapeFollow();
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void tapeFollow()
{
  int P, I, D, error, rightO, leftO, rightI, leftI, control;
  float ki;
  int lasterror = 0;
  int recenterr = 0;
  int q = 1;
  int count = 0;
  int markcount = 0;

  while (digitalRead(49) == HIGH)
  {
    if(pastGate == 0 && right_rotations >= 200) {
      stopMotors();
      delay(20);
      gateCheck();
    }
    ki = 0;
    leftO = analogRead(0);
    leftI = analogRead(1);
    rightI = analogRead(2);
    rightO = analogRead(3);
    
    if ((leftI > threshold) && (rightI > threshold)) {
      error = 0;
      currentSPEED = SPEED;
    } //less then threshold means its off the tape (QRD senses, value of sensor voltage goes up)
    if ((leftI > threshold) && (rightI < threshold) && (leftO < threshold)) {
      error = -1;
      currentSPEED = SPEED;
    }
    if ((leftI < threshold) && (rightI > threshold) && (rightO < threshold)) {
      error = +1;
      currentSPEED = SPEED;
    }
    if ((leftI > threshold) && (leftO > threshold)) {
      error = -2;
      currentSPEED = 0.9 * SPEED;
    }
    if ((rightI > threshold) && (rightO > threshold)) {
      error = +2;
      currentSPEED = 0.9 * SPEED;
    }
    if ((leftO > threshold) && (leftI < threshold)) {
      error = -4;
      currentSPEED = 0.9 * SPEED;
    }
    if ((rightI < threshold) && (rightO > threshold)) {
      error = +4;
      currentSPEED = 0.9 * SPEED;
    }
    if ((leftO < threshold) && (leftI < threshold)) {
      if ((rightI < threshold) && (rightO < threshold)) {
        if (lasterror > 0) error = 6;
        if (lasterror <= 0) error = -6;
        currentSPEED = 0.9 * SPEED;
      }
    }
    
//    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO < threshold) && (markcount > 6)) //three sensor see something, this is the circle start after looped around the tank
//    {
//      stopMotors();
//      if (course == 0 || course == 1)
//      {
//        rotate(45);
//      }
//      else {
//        rotate(-45);
//      }
//      delay(100);
//      error = -2;
//      SPEED = SPEED*.7;
//    }
//    if ((leftI > threshold) && (rightI > threshold) && (leftO > threshold) && (rightO < threshold) && (markcount > 6)) //three sensor see something, this is the circle start after looped around the tank
//    {
//      stopMotors();
//      if (course == 0 || course == 1)
//      {
//        rotate(45);
//      }
//      else {
//        rotate(-45);
//      }
//      delay(100);
//      error = +2;
//      SPEED = SPEED*.7;
//    }

    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold)) { //all sensor see something
      if (markcount == 0)
      {
        LCD.clear(); LCD.home();
        LCD.print("CircleEntrance");
        stopMotors();
        SPEED = 140;
        kp = 30;
        kd = 45;
        delay(100);
        markcount++;
        reverse(7, 150);
        stopMotors();
        if(course == 1 || course == 0)
        {
          rotate(50, 140);
          error = -4;
        }
        else {
          rotate(-50, 140);
          error = +4;
        }

        driveStraight(20, 130);
      }
      else
      {
        error = +100; //100 means stop
        if (markcount > 6)
        {
          markcount++;
          if (course == 0 || course == 1)
          {
            error = -3;
            delay(20);
          }
          else
          {
            error = +3;
            delay(20);
          }
        }
      }
    }

    if (!(error == lasterror)) {
      recenterr = lasterror;
      q++;
    }
    else {
      q = 1;
    }

    P = kp * error;
    D = (int)(kd * (float)(error - recenterr) / (float)(q));
    I = 0;
    
    if(pastGate == 0 && right_rotations >= 200) {
      stopMotors();
      delay(20);
      gateCheck();
    }
    
    control = gain * (P + D + I);

    if (count == 60){
      LCD.clear(); LCD.home();
      LCD.setCursor(0, 0); 
      LCD.print("1K ");
      LCD.print(analogRead(4));
      LCD.setCursor(0, 1); 
      LCD.print("10K ");
      LCD.print(analogRead(5));
      //LCD.setCursor(7,0); LCD.print(int(-SPEED + control)); //printing  FINAL SPEED OF RIGHT
      //LCD.setCursor(7,1); LCD.print(int(SPEED + control));  //PRINTING FINAL SPEED OF LEFT
      //LCD.setCursor(7,0); LCD.print((int)kp);
      //LCD.setCursor(7,1); LCD.print((int)kd);
      //LCD.setCursor(12,0); LCD.print(SPEED);
      count = 0;
    }
    count = count + 1;
    
    if (error != 100) {
      motor.speed(0, currentSPEED - control); //right motor (looking at tina)
      motor.speed(1, currentSPEED + control);  //left motor
      lasterror = error;
    }
    //--------------------------------------------------------------------------------------------------------
    else {
//      if (markcount == 1)
//      {
//        if(course == 1 || course == 0)
//        {
//          rotate(65);
//        }
//        else {
//          rotate(-65);
//        }
//      }
      if (markcount > 0 && markcount <= 6) {
        motor.speed(0, -200);
        motor.speed(1, -200);
        delay(20);
        q = 1;
        leftO = analogRead(0);
        leftI = analogRead(1);
        rightI = analogRead(2);
        rightO = analogRead(3);
        if((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold))
        {
          lasterror = 0;
        }
        if ((leftI > threshold) && (rightI > threshold)) lasterror = 0;
        if ((leftI > threshold) && (rightI < threshold) && (leftO < threshold)) lasterror = -1;
        if ((leftI < threshold) && (rightI > threshold) && (rightO < threshold)) lasterror = +1;
        if ((leftI > threshold) && (leftO > threshold)) lasterror = -2;
        if ((rightI > threshold) && (rightO > threshold)) lasterror = +2;
        if ((leftO > threshold) && (leftI < threshold)) lasterror = -4;
        if ((rightI < threshold) && (rightO > threshold)) lasterror = +4;
        if ((leftO < threshold) && (leftI < threshold)) {
          if ((rightI < threshold) && (rightO < threshold)) {
            if (lasterror > 0) lasterror = 6;
            if (lasterror <= 0) lasterror = -6;
          }
        }
        delay(10); //time reverse
        motor.speed(0, 0);
        motor.speed(1, 0);
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        LCD.setCursor(0, 1);
        LCD.print("le -> ");
        LCD.print(lasterror);
        delay(500);
        if (markcount == 1)
        {
          if (course == 0 || course == 1)
          {
            lasterror = -3;
          }
          else {
            lasterror = 3;
          }
        }
        
//        if (markcount == 1) {
//          stopMotors();
//          if (course == 0 || course == 1)
//          {
//            rotate(45);
//          }
//          else {
//            rotate(-45);
//          }
//        }

        if (markcount == 1) pickUpAgentOne();
        if (markcount == 2) pickUpAgentOne();
        if (markcount == 3) pickUpAgentOne();
        if (markcount == 4) pickUpAgentOne();
        if (markcount == 5) pickUpAgentOne();
        if (markcount == 6) {
          pickUpAgentOne();
          driveToZipline();
        }
      }
//      if (markcount == 8) //can change, this is the mark we go to before we go to the zipline
//      {
//        LCD.clear(); LCD.home();
//        LCD.print("mark -> ");
//        LCD.print(markcount);
//        driveToZipline();
//        //hookZipline(); !!!!!!!!!!!!!!!!!!!!
//        delay(10000); //!!!!!!!!!!!!!!!!!
//      }
      markcount++;
    }
    //--------------------------------------------------------------------------------------------------------
    if(pastGate == 0 && right_rotations >= 200) {
      stopMotors();
      delay(20);
      gateCheck();
    }
  }
}

void gateCheck() {
  //irSensor1 = analogRead(4);
  //irSensor10 = analogRead(5);

  if ( ( analogRead(5) > tenkhzThresh ) || (analogRead(4) > onekhzThresh) ) { 
    motor.speed(0, 0);
    motor.speed(1, 0);
    LCD.clear(); LCD.home();
    LCD.print(irSensor10);
    LCD.print("!!!!!");
    LCD.print(irSensor1);

    if ( (analogRead(5) >= tenkhzThresh) && (analogRead(4) < onekhzThresh)) {
      LCD.clear(); LCD.home();
      LCD.print("10K ");
      LCD.print(analogRead(5));
      while((analogRead(4) < onekhzThresh) && analogRead(5) >= tenkhzThresh)
      {
        delay(10);
        pastGate++;
      }
   }
    else if ( (analogRead(5) < analogRead(4)) && (analogRead(4) >= onekhzThresh)) {
      LCD.clear(); LCD.home();
      LCD.print("1K ");
      LCD.print(analogRead(4));
      int step1 = 0;
      while((analogRead(5) < analogRead(4)) && (analogRead(4) >= onekhzThresh))
      {
        delay(10);
        step1++;
      }
      LCD.clear(); LCD.home();
      LCD.print("1");
      //delay(100);
      while((analogRead(4) < onekhzThresh) && (analogRead(5) >= tenkhzThresh) && step1 != 0)
      {
        pastGate++;
        delay(10);
      }
    } 
  }
}

void driveToZipline() {
  moveArmToStartPosition();
  LCD.clear(); LCD.home();
  LCD.print("Finding");
  LCD.setCursor(0,1);
  LCD.print("zipline");
  reverse(27, 130);
  delay(1000);
  if (course == 1 || course == 0)
  {
    rotate(50, 150);
    delay(500);
  }
  else
  {
    rotate(-50, 150);
    delay(500);
  }
  
  reverse(100, 130);
  delay(500);
  if (course == 1 || course == 0)
  {
    rotate(45, 150);
    delay(500);
  }
  else
  {
    rotate(-45, 150);
    delay(300);
  }
  grabZiplineMechanismAndLift();
  reverse(205, 130);
  motor.speed(2, -255);
  delay(openTime);
  motor.speed(2, 0);
  driveStraight(25, 130);
  stopMotors();
}


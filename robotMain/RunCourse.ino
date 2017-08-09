float irSensor1 = 0;
float irSensor10 = 0;
int hillIRDelayStart = 0;

void runCourse()
{
  pastGate = false;
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
  int sharpRightControl = 400;
  int sharpLeftControl = -400;

  while (digitalRead(49) == HIGH)
  {
    if(pastGate == false) {
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
      error = -3;
      currentSPEED = 0.9 * SPEED;
    }
    if ((rightI < threshold) && (rightO > threshold)) {
      error = +3;
      currentSPEED = 0.9 * SPEED;
    }
    if ((leftO < threshold) && (leftI < threshold)) {
      if ((rightI < threshold) && (rightO < threshold)) {
        if (lasterror > 0) error = 5;
        if (lasterror <= 0) error = -5;
        currentSPEED = 0.9 * SPEED;
      }
    }
    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO < threshold) && (markcount > 6)) //three sensor see something, this is the circle start after looped around the tank
    {
      if(course == 0 || course == 1)
      {
        rotate(80);
      }
      else {
        rotate(-80);
      }
          delay(100);
          error = -2;
          SPEED = SPEED*.7;
    }
    if ((leftI > threshold) && (rightI > threshold) && (leftO > threshold) && (rightO < threshold) && (markcount > 6)) //three sensor see something, this is the circle start after looped around the tank
    {
      if(course == 0 || course == 1)
      {
        rotate(80);
      }
      else {
        rotate(-80);
      }
      delay(100);
      error = +2;
      SPEED = SPEED*.7;
    }
    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold)) { //all sensor see something
      if (markcount == 0)
      {
        driveStraight(30,200);
        markcount++;
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

    control = gain * (P + D + I);

    if(pastGate == false) {
      gateCheck();
    }

    if (count == 50){
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
//      if (markcount == 1) {
//        LCD.clear(); LCD.home();
//        LCD.print("mark -> ");
//        LCD.print(markcount);
//        motor.speed(0, +200);
//        motor.speed(1, -200);
//        if(course == 1 || course == 0)
//        {
//          motor.speed(0, -currentSPEED*.4 + sharpRightControl); //right motor (looking at tina)
//          motor.speed(1, -currentSPEED*1.2 + sharpRightControl);  //left motor
//          //lasterror = +3;
//          //delay(1000);
//        }
//        else
//        {
//          motor.speed(0, currentSPEED*.4 + sharpLeftControl); //right motor (looking at tina)
//          motor.speed(1, currentSPEED*1.2 + sharpLeftControl);  //left motor
//          //lasterror = -3;
//          //delay(1000);
//        }
//        delay(100);
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
        if ((leftO > threshold) && (leftI < threshold)) lasterror = -3;
        if ((rightI < threshold) && (rightO > threshold)) lasterror = +3;
        if ((leftO < threshold) && (leftI < threshold)) {
          if ((rightI < threshold) && (rightO < threshold)) {
            if (lasterror > 0) lasterror = 5;
            if (lasterror <= 0) lasterror = -5;
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
        delay(1000);
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
        if (markcount == 1) pickUpAgentOne();
        if (markcount == 2) pickUpAgentTwo();
        if (markcount == 3) pickUpAgentThree();
        if (markcount == 4) pickUpAgentFour();
        if (markcount == 5) pickUpAgentFive();
        if (markcount == 6) {
          pickUpAgentSix();
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
    if(pastGate == false) {
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
    LCD.print(" ");
    LCD.print(irSensor1);
    //delay(2000);

    if ( (analogRead(5) >= tenkhzThresh) && (analogRead(4) < onekhzThresh)) {
      LCD.clear(); LCD.home();
      LCD.print("10K ");
      LCD.print(analogRead(5));
      while((analogRead(4) < onekhzThresh) && analogRead(5) >= tenkhzThresh)
      {
        delay(10);
        pastGate = true;
      }
   }
    else if ( (analogRead(5) < analogRead(4)) && (analogRead(4) >= onekhzThresh)) {
      LCD.clear(); LCD.home();
      LCD.print("1K ");
      LCD.print(analogRead(4));
      while((analogRead(5) < analogRead(4)) && (analogRead(4) >= onekhzThresh))
      {
        delay(10);
        pastGate = true;
      }
      LCD.clear(); LCD.home();
      LCD.print("1");
      delay(100);
      while((analogRead(4) < onekhzThresh) && (analogRead(5) >= tenkhzThresh) && pastGate == true)
      {
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

  reverse(200, 150);
  if (course == 1 || course == 0)
  {
    rotate(45);
    delay(300);
  }
  else
  {
    rotate(-45);
    delay(300);
  }
  
  grabZiplineMechanismAndLift();
  reverse(90, 130);
  motor.speed(2, -255);
  delay(openTime);
  motor.speed(2, 0);
  driveStraight(25, 130);
  stopMotors();

}


float irSensor1 = 0;
float irSensor10 = 0;
int timeStart;
int adjustForGate = 0;

void runCourse()
{
  pastGate = 0;
  LCD.clear(); LCD.home();
  LCD.print("Tape Following");
  moveArmToStartPosition();
  delay(1000); 
  timeStart = millis();
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
    if (millis() - timeStart > 1900 && adjustForGate == 0)
    {
      RCServo0.write(130);
      RCServo1.write(180-130);
      adjustForGate++;
    }
    if(pastGate == 0) {
      gateCheck();
    }
    ki = 0;
    leftO = analogRead(3);
    leftI = analogRead(2);
    rightI = analogRead(1);
    rightO = analogRead(0);
    
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
      currentSPEED = 0.8 * SPEED;
    }
    if ((rightI > threshold) && (rightO > threshold)) {
      error = +2;
      currentSPEED = 0.8 * SPEED;
    }
    if ((leftO > threshold) && (leftI < threshold)) {
      error = -3;
      currentSPEED = 0.65 * SPEED;
    }
    if ((rightI < threshold) && (rightO > threshold)) {
      error = +3;
      currentSPEED = 0.65 * SPEED;
    }
    if ((leftO < threshold) && (leftI < threshold)) {
      if ((rightI < threshold) && (rightO < threshold)) {
        if (lasterror > 0) error = 5;
        if (lasterror <= 0) error = -5;
        currentSPEED = 0.8 * SPEED;
      }
    }
    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold)) { //all sensor see something
      error = +100; //100 means stop
    }
    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold)) //three sensor see somethign, this is the circle start after looped around the tank
    {
      error = 0;
      currentSPEED = 0.65 * SPEED;
    }
    if ((leftI > threshold) && (rightI > threshold) && (leftO > threshold)) //three sensor see somethign, this is the circle start after looped around the tank
    {
      error = 0;
      currentSPEED = 0.65 * SPEED;
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

    if(pastGate == 0) {
      gateCheck();
    }

    if (count == 50)
    {
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
      motor.speed(0, -currentSPEED + control); //right motor (looking at tina)
      motor.speed(1, currentSPEED + control);  //left motor
      lasterror = error;
    }
    //--------------------------------------------------------------------------------------------------------
    else {
      if (markcount == 0) {
        if(course == 1 || course == 0)
        {
          motor.speed(0, -currentSPEED + sharpRightControl); //right motor (looking at tina)
          motor.speed(1, currentSPEED + sharpRightControl);  //left motor
        }
        else
        {
          motor.speed(0, -currentSPEED + sharpLeftControl); //right motor (looking at tina)
          motor.speed(1, currentSPEED + sharpLeftControl);  //left motor
        }
        delay(200);
      }
      if (markcount > 0 && markcount <= 6) {
        motor.speed(0, +200);
        motor.speed(1, -200);
        q = 1;
        leftO = analogRead(3);
        leftI = analogRead(2);
        rightI = analogRead(1);
        rightO = analogRead(0);
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
        delay(50); //time reverse
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        LCD.setCursor(0, 1);
        LCD.print("le -> ");
        LCD.print(lasterror);
        motor.speed(0, 0);
        motor.speed(1, 0);
        if (markcount == 1) pickUpAgentOne();
        if (markcount == 2) pickUpAgentTwo();
        if (markcount == 3) pickUpAgentThree();
        if (markcount == 4) pickUpAgentFour();
        if (markcount == 5) pickUpAgentFive();
        if (markcount == 6) pickUpAgentSix();
      }
      if (markcount > 6 && markcount != 8) //just skip over these marks
      {
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        LCD.setCursor(0, 1);
        LCD.print("le -> ");
        motor.speed(0, -150);
        motor.speed(1, +150);
      }
      if (markcount == 8) //can change, this is the mark we go to before we go to the zipline
      {
        driveToZipline();
        //hookZipline(); !!!!!!!!!!!!!!!!!!!!
        delay(10000); //!!!!!!!!!!!!!!!!!
      }
      markcount = markcount + 1;
    }
    //--------------------------------------------------------------------------------------------------------
    if(pastGate == 0) {
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
        pastGate++;
      }
   }
    else if ( (analogRead(5) < tenkhzThresh) && (analogRead(4) >= onekhzThresh)) {
      LCD.clear(); LCD.home();
      LCD.print("1K ");
      LCD.print(analogRead(4));
      while((analogRead(5) < tenkhzThresh) && (analogRead(4) >= onekhzThresh))
      {
        delay(10);
        pastGate++;
      }
      LCD.clear(); LCD.home();
      LCD.print("1");
      delay(100);
      while((analogRead(4) < onekhzThresh) && (analogRead(5) >= tenkhzThresh) && pastGate != 0)
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
  
  int inputButton =1; //change
  float timeStart = millis();
  float timeDrive = 3000;
  motor.speed(0, -130);
  motor.speed(1, +130);
  while( (millis() - timeStart) < timeDrive ) {
    if ((millis() - timeStart) > timeDrive-timeDrive*.2)
    {
      motor.speed(0, -110);
      motor.speed(1, +110);
    }
//    if( digitalRead(inputButton) == HIGH ){
//      break;
//    }
  }
  motor.speed(0,0);
  motor.speed(1,0);
}

void hookZipline()
{
  // grab mechanism -------
  baseServo.write(100);
  RCServo2.write(90);
  delay(300);
  RCServo0.write(100);
  RCServo1.write(180-100);
  motor.speed(2, 200);
  delay(4000);
  motor.speed(2, 50);
  // ----------------------

  if(course == 1 || course == 0)
  {
    RCServo2.write(180);
    RCServo0.write(0);
    RCServo1.write(180-0);
    delay(200);
    RCServo2.write(80);
    delay(200);
    baseServo.write(100);
    delay(1000);
  }
  else
  {
    RCServo2.write(180);
    RCServo0.write(0);
    RCServo1.write(180-0);
    delay(200);
    RCServo2.write(80);
    delay(200);
    baseServo.write(80);
    delay(1000);
  }
  
}



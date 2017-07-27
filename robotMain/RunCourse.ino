void runCourse()
{
  LCD.clear(); LCD.home();
  LCD.print("Tape Following");
  delay(1000);
  tapeFollow();
  motor.speed(0, 0);
  motor.speed(1, 0);
}

//void alignToZipline()
//{
//  float leftIR = analogRead(2); //if these are changed, must change in IRmenu as well
//  float rightIR = analogRead(3); //!!!!!!!!^^^^^^^^^^^!!!!!!!!!
//  float uncertainty = .1;
//  while (leftIR > rightIR * rightSensorCorrection + rightIR * rightSensorCorrection * uncertainty || leftIR > rightIR * rightSensorCorrection - rightIR * rightSensorCorrection * uncertainty)
//  {
//    if (leftIR > rightIR * rightSensorCorrection)
//    {
//      motor.speed(0, 0); //turn left
//      motor.speed(1, 150);
//    }
//    else {
//      motor.speed(0, -150); //turn right
//      motor.speed(1, 0);
//    }
//  }
//  motor.speed(0, 0);
//  motor.speed(1, 0);
//}

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
      currentSPEED = 0.7 * SPEED;
    }

    if ((rightI > threshold) && (rightO > threshold)) {
      error = +2;
      currentSPEED = 0.7 * SPEED;
    }


    if ((leftO > threshold) && (leftI < threshold)) {
      error = -3;
      currentSPEED = 0.55 * SPEED;
    }
    if ((rightI < threshold) && (rightO > threshold)) {
      error = +3;
      currentSPEED = 0.55 * SPEED;
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

    if (count == 30)
    {
      LCD.clear(); LCD.home();
      LCD.print("LO ");
      LCD.setCursor(0, 0); LCD.print(leftO);
      LCD.print(" LI ");
      LCD.print(leftI);
      LCD.setCursor(1, 0); 
      LCD.print("RO ");
      LCD.print(rightO);
      LCD.print(" RI ");
      LCD.print(rightI);
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
      if (markcount == -1) { //!!!!!!!!!!!!!!!!!!!!
        motor.speed(0, -currentSPEED + sharpRightControl); //right motor (looking at tina)
        motor.speed(1, currentSPEED + sharpRightControl);  //left motor
        delay(200);
      }
      if (markcount >= 0 && markcount <= 6) { //!!!!!!!!!!!!!!!!!!!!
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
        delay(100); //time reverse
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        LCD.setCursor(0, 1);
        LCD.print("le -> ");
        LCD.print(lasterror);
        motor.speed(0, 0);
        motor.speed(1, 0);
        delay(4000); //do arm stuff here instead
      }
      if (markcount > 6 && markcount != 10) //just skip over these marks
      {
        motor.speed(0, -150);
        motor.speed(1, +150);
      }
      if (markcount == 10) //can change, this is the mark we go to before we go to the zipline
      {
        // alignToZipline();
      }
      markcount = markcount + 1;
    }
    //--------------------------------------------------------------------------------------------------------
    if(pastGate == 0) {
      gateCheck();
    }
  }
}

float Sensor1Total = 0;
float Sensor10Total = 0;
int maxCount = 20;
int tenkhzThresh = 5; //change
int onekhzThresh = 5; //change
int switchCount = 0;
int variationThresh = 10;
float lastIRSensor1;
float lastIRSensor10;
float possibleChange1;
float possibleChange10;
float irSensor1;
float irSensor10;

void gateCheck() {
  Sensor1Total = 0;
  Sensor10Total = 0;
  switchCount = 0;

  for (int counter = 0; counter < maxCount; counter++)
  {
    Sensor1Total += analogRead(4);
    Sensor10Total += analogRead(5);
    delay(2);
  }
  irSensor1 = Sensor1Total / maxCount;
  irSensor10 = Sensor10Total / maxCount;

  if ( ( irSensor10 > tenkhzThresh ) || (irSensor1 > onekhzThresh) ) {
    motor.speed(0, 0);
    motor.speed(1, 0);
    lastIRSensor1 = irSensor1;
    lastIRSensor10 = irSensor10;

    if ( irSensor10 > tenkhzThresh && irSensor1 < onekhzThresh) {
      while ( switchCount < 1 ) {
        Sensor1Total = 0;
        Sensor10Total = 0;
        for ( int counter = 0; counter < maxCount; counter++)
        {
          Sensor1Total += analogRead(4);
          Sensor10Total +=analogRead(5);
          delay(2); 
         }
         irSensor1 = Sensor1Total / maxCount;
         irSensor10 = Sensor10Total / maxCount;
         possibleChange10 = lastIRSensor10 - irSensor10;
         possibleChange1 = lastIRSensor1 - irSensor1;
         if ( abs(possibleChange10) > variationThresh && abs(possibleChange1) > variationThresh ) 
         {
          switchCount ++;
         }
         lastIRSensor1 = irSensor1;
         lastIRSensor10 = irSensor10;
      }
   }

    if ( irSensor10 < tenkhzThresh && irSensor1 > onekhzThresh) {
      while ( switchCount < 2 ) {
        Sensor1Total = 0;
        Sensor10Total = 0;
        for ( int counter = 0; counter < maxCount; counter++)
        {
          Sensor1Total += analogRead(4);
          Sensor10Total +=analogRead(5);
          delay(2); 
         }
         irSensor1 = Sensor1Total / maxCount;
         irSensor10 = Sensor10Total / maxCount;
         possibleChange10 = lastIRSensor10 - irSensor10;
         possibleChange1 = lastIRSensor1 - irSensor1;
         if ( abs(possibleChange10) > variationThresh && abs(possibleChange1) > variationThresh ) 
         {
          switchCount ++;
         }
         lastIRSensor1 = irSensor1;
         lastIRSensor10 = irSensor10;
      }
    } 
   pastGate++;
  }
}



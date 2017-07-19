void runCourse()
{
  LCD.clear(); LCD.home();
  LCD.print("Tape Following");
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
    ki = 0;
    leftO = analogRead(0);
    leftI = analogRead(1);
    rightI = analogRead(4);
    rightO = analogRead(5);

    if ((leftI > threshold) && (rightI > threshold)) {
      error = 0;
    } //less then threshold means its off the tape (QRD senses, value of sensor voltage goes up)

    if ((leftI > threshold) && (rightI < threshold) && (leftO < threshold)) {
      error = -1;
    }
    if ((leftI < threshold) && (rightI > threshold) && (rightO < threshold)) {
      error = +1;
    }

    if ((leftI > threshold) && (leftO > threshold)) error = -2;
    if ((rightI > threshold) && (rightO > threshold)) error = +2;

    if ((leftO > threshold) && (leftI < threshold)) error = -3;
    if ((rightI < threshold) && (rightO > threshold)) error = +3;

    if ((leftO < threshold) && (leftI < threshold)) {
      if ((rightI < threshold) && (rightO < threshold)) {
        if (lasterror > 0) error = 5;
        if (lasterror <= 0) error = -5;
      }
    }

    if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold)) { //all sensor see something
      error = +100; //100 means stop
    }


    // if((leftO>threshold)&&(leftI>threshold)){
    // if((rightI>threshold)&&(right)>threshold)){
    //     timePassed=millis()- t_initial
    //     setStrategy();
    //   }
    // }


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
      LCD.setCursor(0, 0); LCD.print(control);
      LCD.setCursor(0, 1); LCD.print(lasterror);
      LCD.setCursor(7, 0); LCD.print(leftI);
      LCD.setCursor(7, 1); LCD.print(rightI);
      //LCD.setCursor(7,0); LCD.print(int(-SPEED + control)); //printing  FINAL SPEED OF RIGHT
      //LCD.setCursor(7,1); LCD.print(int(SPEED + control));  //PRINTING FINAL SPEED OF LEFT
      //LCD.setCursor(7,0); LCD.print((int)kp);
      //LCD.setCursor(7,1); LCD.print((int)kd);
      //LCD.setCursor(12,0); LCD.print(SPEED); //printing speed
      count = 0;
    }
    count = count + 1;

    if (error != 100) {
      motor.speed(0, -SPEED + control); //right motor (looking at tina)
      motor.speed(1, SPEED + control);  //left motor
      lasterror = error;
    }
    else {
      if (markcount == 0) {
        motor.speed(0, -SPEED + sharpLeftControl); //right motor (looking at tina)
        motor.speed(1, SPEED + sharpLeftControl);  //left motor
        delay(200);
      }
      if (markcount > 0) {
        motor.speed(0, 0);
        motor.speed(1, 0);
        LCD.clear(); LCD.home(); LCD.print(markcount);
        delay(5000);
      }
      markcount = markcount + 1;
    }
  }
}


float irSensor10, irSensor1;
int timeStart;
int adjustForGate = 0;
int error, rightO, leftO, rightI, leftI, control;
int lasterror = 0;
int markcount = 0;

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
  int P, I, D;
  float ki;
  int recenterr = 0;
  int q = 1;
  int count = 0;
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
    
    if(pastGate == 0) gateCheck();
    
    error = qrdSense(); //gets the error for normal conditions with QRDs
    updateSpeed(); //updates currentspeed
    specialCaseQrdSense(); //for the "special" cases for tapefollowing like 3 sensors sees, or all sees, updates speed/error as well
    
    if (!(error == lasterror)) {
      recenterr = lasterror;
      q++;
    }
    else q = 1;

    P = kp * error;
    D = (int)(kd * (float)(error - recenterr) / (float)(q));
    control = gain * (P + D);

    if(pastGate == 0) gateCheck();

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
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        motor.speed(0, +200);
        motor.speed(1, -200);
        if(course == 1 || course == 0)
        {
          motor.speed(0, -currentSPEED*.4 + sharpRightControl); //right motor (looking at tina)
          motor.speed(1, -currentSPEED*1.2 + sharpRightControl);  //left motor
          //lasterror = +3;
          //delay(1000);
        }
        else
        {
          motor.speed(0, currentSPEED*.4 + sharpLeftControl); //right motor (looking at tina)
          motor.speed(1, currentSPEED*1.2 + sharpLeftControl);  //left motor
          //lasterror = -3;
          //delay(1000);
        }
        delay(100);
      }
      if (markcount > 0 && markcount <= 6) {
        motor.speed(0, +200);
        motor.speed(1, -200);
        delay(20);
        q = 1;
        
        lasterror = qrdSense();
        if((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold)) lasterror = 0; //this condition wasnt inside the qrdSense function
        
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
//        if (markcount == 1) pickUpAgentOne();
//        if (markcount == 2) pickUpAgentTwo();
//        if (markcount == 3) pickUpAgentThree();
//        if (markcount == 4) pickUpAgentFour();
//        if (markcount == 5) pickUpAgentFive();
//        if (markcount == 6) pickUpAgentSix();
      }
      if (markcount == 8) //can change, this is the mark we go to before we go to the zipline
      {
        LCD.clear(); LCD.home();
        LCD.print("mark -> ");
        LCD.print(markcount);
        driveToZipline();
        //hookZipline(); !!!!!!!!!!!!!!!!!!!!
        delay(10000); //!!!!!!!!!!!!!!!!!
      }
      LCD.clear(); LCD.home();
      LCD.print("HERE");
      markcount++;
    }
    if(pastGate == 0) {
      gateCheck();
    }
  }
}
//-------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------
void driveToZipline() {
  moveArmToStartPosition();
  LCD.clear(); LCD.home();
  LCD.print("Finding");
  LCD.setCursor(0,1);
  LCD.print("zipline");
  if (course == 1 || course == 0)
  {
    motor.speed(0, -130);
    motor.speed(1, 0);
    LCD.clear(); LCD.home();
    LCD.print("Correction");
    LCD.setCursor(0,1);
    LCD.print("left");
    delay(300);
  }
  else
  {
    motor.speed(0, 0);
    motor.speed(1, +130);
    LCD.clear(); LCD.home();
    LCD.print("Correction");
    LCD.setCursor(0,1);
    LCD.print("right");
    delay(300);
  }
  int inputButton =1; //change
  float timeStart = millis();
  float timeDrive = 3000;
  motor.speed(0, -130);
  motor.speed(1, +130);
  LCD.clear(); LCD.home();
  LCD.print("Forward");
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
//--------------------------------------------------------------------------------------------
void hookZipline()
{
  // grab mechanism -------
  baseServoPosition(100,1);
  foreArmPosition(90,1);
  delay(300);
  backArmPosition(100,1);
  motor.speed(2, 200);
  delay(4000);
  motor.speed(2, 50);
  
  if(course == 1 || course == 0)
  {
    foreArmPosition(180,1);
    backArmPosition(0,1);
    delay(200);
    foreArmPosition(80,1);
    delay(200);
    baseServoPosition(100,1);
    delay(1000);
  }
  else
  {
    foreArmPosition(180,1);
    backArmPosition(0,1);
    delay(200);
    foreArmPosition(80,1);
    delay(200);
    baseServoPosition(80,1);
    delay(1000);
  }
}
//-----------------------------------------------------------------------------------------
int qrdSense() {
  leftO = analogRead(0);
  leftI = analogRead(1);
  rightI = analogRead(2);
  rightO = analogRead(3);
  
  int error = 0;
  if ((leftI > threshold) && (rightI > threshold)) error = 0; 
  if ((leftI > threshold) && (rightI < threshold) && (leftO < threshold)) error = -1;
  if ((leftI < threshold) && (rightI > threshold) && (rightO < threshold)) error = +1;
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
  return error;
}
//-----------------------------------------------------------------------------------------------------------
void updateSpeed() {
  if( error == 0 || error == +1 || error == -1 || error == 5 || error == -5) currentSPEED = SPEED;
  if( error == -2 || error == +2) currentSPEED = 0.8*SPEED;
  if( error == -3 || error == +3) currentSPEED = 0.65*SPEED;
}
//------------------------------------------------------------------------------------------------------------------------
void specialCaseQrdSense() {
  leftO = analogRead(0);
  leftI = analogRead(1);
  rightI = analogRead(2);
  rightO = analogRead(3); 
  int error = 0; 
  
  if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO < threshold) && (markcount > 6))
  {//three sensor see something, this is the circle start after looped around the tank
    error = 1;
    currentSPEED = 0.65*SPEED;
    delay(20);
  }
  if ((leftI > threshold) && (rightI > threshold) && (leftO > threshold) && (rightO < threshold) && (markcount > 6))
  {//three sensor see something, this is the circle start after looped around the tank
    error = -1;
    currentSPEED = 0.65*SPEED;
    delay(20); 
  }
  if ((leftI > threshold) && (rightI > threshold) && (rightO > threshold) && (leftO > threshold))
  {// all sensor sees something
    error = +100; //100 means stop
    markcount++;
    if (markcount > 6) { 
      if (course == 0 || course == 1) error = -1;
      else error = +1;
      delay(20);
    }
  }
}

void runCourse()
{
  
}

void tapeFollow()
{
  int P, I, D, error, right, left, recenterr, control;
  float ki;
  int lasterror = 0;
  int q = 1;
  int count = 0;
  while(true)
  {
    ki = 0;
    right = analogRead(2);
    left = analogRead(4);
    if ((left>threshold)&&(right>threshold)) error = 0; 
    if ((left>threshold)&&(right<threshold)) error = -1; 
    if ((left<threshold)&&(right>threshold)) error = +1; 
    if ((left<threshold)&&(right<threshold))
    {
      if (lasterror>0) error = 5; 
      if (lasterror<=0) error=-5;
    }
    if (!(error==lasterror))
    { 
      recenterr=lasterror; 
      q++;
    }
    else {
      q=1;
    }
    P=kp*error; 
    D=(int)(kd*(float)(error-recenterr)/(float)(q)); 
    I = 0;
    
    control = gain*(P+D+I);
    if (count==30)
    {
      LCD.clear();
      LCD.setCursor(0,0); LCD.print(right); 
      LCD.setCursor(0,1); LCD.print(left);
      //LCD.setCursor(7,0); LCD.print(int(-SPEED + control));
      //LCD.setCursor(7,1); LCD.print(int(SPEED + control));
      LCD.setCursor(7,0); LCD.print((int)kp);
      LCD.setCursor(7,1); LCD.print((int)kd);
      //LCD.setCursor(12,0); LCD.print(SPEED);
      count=0;
    } 
    count=count+1;
    motor.speed(0, -SPEED + control);
    motor.speed(1, SPEED + control);
    lasterror=error;
  }
}


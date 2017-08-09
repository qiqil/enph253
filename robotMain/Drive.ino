void driveMenu()
{
  while(digitalRead(49) == HIGH)
  {
    double arrow = analogRead(7);
    int select;

    if (arrow >= 0 && arrow < 1013/5) 
    {
      select = 1;
      LCD.clear(); LCD.home();
      LCD.print("->kp   kd   gain");
      LCD.setCursor(0,1);
      LCD.print("  speed   thresh");     
    }
    else if (arrow >= 1013/5 && arrow < 1013*2/5) 
    {
      select = 2;
      LCD.clear(); LCD.home();
      LCD.print("  kp ->kd   gain");
      LCD.setCursor(0,1);
      LCD.print("  speed   thresh");  
    }
    else if (arrow >=1013*2/5 && arrow < 1013*3/5)
    {
      select = 3;
      LCD.clear(); LCD.home();
      LCD.print("  kp   kd ->gain");
      LCD.setCursor(0,1);
      LCD.print("  speed   thresh"); 
    }
    else if (arrow >=1013*3/5 && arrow < 1013*4/5)
    {
      select = 4;
      LCD.clear(); LCD.home();
      LCD.print("  kp   kd   gain");
      LCD.setCursor(0,1);
      LCD.print("->speed   thresh"); 
    }
    else if (arrow >=1013*4/5 && arrow <= 1020)
    {
      select = 5;
      LCD.clear(); LCD.home();
      LCD.print("  kp   kd   gain");
      LCD.setCursor(0,1);
      LCD.print("  speed ->thresh"); 
    }
    delay(100);
    int buttonON = digitalRead(50);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(select == 1)
      {
        kpMenu();
      }
      else if(select == 2)
      {
        kdMenu();
      }
      else if(select == 3)
      {
        gainMenu();
      }
      else if(select == 4)
      {
        speedMenu();
      }
      else if(select == 5)
      {
        thresholdMenu();
      }
    }
    delay(150);
  }
  while(digitalRead(49) == LOW){}
}

void kpMenu()
{
  float value;
  while(digitalRead(49) == HIGH)
  {
    value = analogRead(6)/10;
    LCD.clear(); LCD.home();
    LCD.print("kp: ");
    LCD.print(value);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(kp);

    if(digitalRead(50) == LOW)
    {
      kp = value;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void kdMenu()
{
  float value;
  while(digitalRead(49) == HIGH)
  {
    value = analogRead(6)/10;
    LCD.clear(); LCD.home();
    LCD.print("kd: ");
    LCD.print(value);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(kd);

    if(digitalRead(50) == LOW)
    {
      kd = value;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void gainMenu()
{
  float value;
  while(digitalRead(49) == HIGH)
  {
    value = analogRead(6)/50;
    LCD.clear(); LCD.home();
    LCD.print("gain: ");
    LCD.print(value);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(gain);

    if(digitalRead(50) == LOW)
    {
      gain = value;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void speedMenu()
{
  float value;
  while(digitalRead(49) == HIGH)
  {
    value = analogRead(6)/5;
    LCD.clear(); LCD.home();
    LCD.print("speed: ");
    LCD.print(value);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(SPEED);

    if(digitalRead(50) == LOW)
    {
      SPEED = value;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void thresholdMenu()
{
  float value;
  while(digitalRead(49) == HIGH)
  {
    value = analogRead(6)/2;
    LCD.clear(); LCD.home();
    LCD.print("threshold: ");
    LCD.print(value);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(threshold);

    if(digitalRead(50) == LOW)
    {
      threshold = value;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}




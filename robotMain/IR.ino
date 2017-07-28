void irMenu()
{
  while(digitalRead(49) == HIGH)
  {
    double arrow = analogRead(7);
    int select;
  
    if (arrow >= 0 && arrow < 1013/2) 
    {
      select = 1;
      LCD.clear(); LCD.home();
      LCD.print("->threshold");
      LCD.setCursor(0,1);
      LCD.print("  IR vals");
    }
    else
    {
      select = 2;
      LCD.clear(); LCD.home();
      LCD.print("  threshold");
      LCD.setCursor(0,1);
      LCD.print("->IR vals");
    }
    int buttonON = digitalRead(50);
    delay(100);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(select == 1)
      {
        setIRThresh();
      }
      else if(select == 2)
      {
        currentIR();
      }
    }
  }
  while(digitalRead(49) == LOW){}
}

void currentIR()
{
  while(digitalRead(49) == HIGH)
  {
    float tenKIR = analogRead(5);
    float oneKIR = analogRead(4);
    LCD.clear(); LCD.home();
    LCD.print("1K ");
    LCD.print(oneKIR);
    LCD.setCursor(0,1);
    LCD.print("10K ");
    LCD.print(tenKIR);
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void setIRThresh()
{
  while(digitalRead(49) == HIGH)
  {
    double arrow = analogRead(7);
    int select;
  
    if (arrow >= 0 && arrow < 1013/2) 
    {
      select = 1;
      LCD.clear(); LCD.home();
      LCD.print("->1K thresh");
      LCD.setCursor(0,1);
      LCD.print("  10K thresh");
    }
    else
    {
      select = 2;
      LCD.clear(); LCD.home();
      LCD.print("  1K thresh");
      LCD.setCursor(0,1);
      LCD.print("->10K thresh");
    }
    int buttonON = digitalRead(50);
    delay(100);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(select == 1)
      {
        set1Kthresh();
      }
      else if(select == 2)
      {
        set10Kthresh();
      }
    }
  }
  while(digitalRead(49) == LOW){}
}

void set1Kthresh()
{
  float val;
  while(digitalRead(49) == HIGH)
  {
    val = analogRead(6)/4;
    LCD.clear(); LCD.home();
    LCD.print("Set 1K: ");
    LCD.print(val);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(onekhzThresh);
    if(digitalRead(50) == LOW)
    {
      onekhzThresh = val;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void set10Kthresh()
{
  float val;
  while(digitalRead(49) == HIGH)
  {
    val = analogRead(6)/4;
    LCD.clear(); LCD.home();
    LCD.print("Set 10K: ");
    LCD.print(val);
    LCD.setCursor(0,1);
    LCD.print("Current: ");
    LCD.print(tenkhzThresh);
    if(digitalRead(50) == LOW)
    {
      tenkhzThresh = val;
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}


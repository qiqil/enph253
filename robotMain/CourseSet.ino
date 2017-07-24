void courseSetMenu() 
{
  while(digitalRead(49) == HIGH)
  {
    double arrow = analogRead(7);
    int select;
  
    if (arrow >= 0 && arrow < 1013/2) 
    {
      select = 1;
      LCD.clear(); LCD.home();
      LCD.print("->left     right");
      currentPrint();
    }
    else
    {
      select = 2;
      LCD.clear(); LCD.home();
      LCD.print("  left   ->right");
      currentPrint();
    }
    int buttonON = digitalRead(50);
    delay(100);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(select == 1)
      {
        course = 2;
      }
      else if(select == 2)
      {
        course = 1;
      }
    }
  }
  while(digitalRead(49) == LOW){}
}

void currentPrint()
{
  LCD.setCursor(0,1);
  LCD.print("Current: ");
  if(course == 0)
  {
    LCD.print("None");
  }
  else if(course == 1)
  {
    LCD.print("right");
  }
  else
  {
    LCD.print("left");
  }
}


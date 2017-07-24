void optionsMenu()
{
  while(digitalRead(49) == HIGH)
  {
    LCD.clear(); LCD.home();
    double subMenu = 0;
    double arrow = analogRead(7);
    if (arrow >= 0 && arrow < 1013/4)
    {
      subMenu = 1;
      LCD.clear(); LCD.home();
      LCD.print("->Drive   Course");
      LCD.setCursor(0,1);
      LCD.print("  IR    Strategy");
    }
    else if (arrow >= 1013/4 && arrow < 1013/2)
    {
      subMenu = 2;
      LCD.clear(); LCD.home();
      LCD.print("  Drive ->Course");
      LCD.setCursor(0,1);
      LCD.print("  IR    Strategy");
    }
    else if (arrow >= 1013/2 && arrow < 1013*3/4)
    {
      subMenu = 3;
      LCD.clear(); LCD.home();
      LCD.print("  Drive   Course");
      LCD.setCursor(0,1);
      LCD.print("->IR    Strategy");
    }
    else if (arrow >= 1013*3/4 && arrow <= 1020)
    {
      subMenu = 4;
      LCD.clear(); LCD.home();
      LCD.print("  Drive   Course");
      LCD.setCursor(0,1);
      LCD.print("  IR  ->Strategy");
    }
    delay(100);
    int buttonON = digitalRead(50);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(subMenu == 1)
      {
        driveMenu();
      }
      else if(subMenu == 2)
      {
        courseSetMenu();
      }
      else if(subMenu == 3)
      {
        irMenu();
      }
      else if(subMenu == 4)
      {
        strategyMenu();
      }
    }
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}


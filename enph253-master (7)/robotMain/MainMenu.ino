void mainMenu()
{
    double select = 0;
    double arrow = analogRead(7);
    if (arrow >= 0 && arrow < 1020/2)
    {
      select = 1;
      LCD.clear(); LCD.home();
      LCD.print("->Start");
      LCD.setCursor(0,1);
      LCD.print("  Options");
    }
    else
    {
      select = 2;
      LCD.clear(); LCD.home();
      LCD.print("  Start");
      LCD.setCursor(0,1);
      LCD.print("->Options");
    }
    delay(100);
    int buttonON = digitalRead(50);
    if(buttonON == LOW)
    {
      while(digitalRead(50) == LOW){}
      if(select == 1)
      {
        runCourse();
      }
      else if(select == 2)
      {
        optionsMenu();
      }
    }    
}


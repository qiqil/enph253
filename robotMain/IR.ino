void irMenu()
{
  float tenKTotal;
  float oneKTotal;
  int maxCount = 20;
  while(digitalRead(49) == HIGH)
  {
    tenKTotal = 0;
    oneKTotal = 0;
    for(int count = 0; count<maxCount; count++)
    {
      tenKTotal += analogRead(5);
      oneKTotal += analogRead(4);
      delay(2);
    }
    float tenKIR = tenKTotal/maxCount;
    float oneKIR = oneKTotal/maxCount; 
    LCD.clear(); LCD.home();
    LCD.print("1K ");
    LCD.print(oneKIR);
    LCD.setCursor(0,1);
    LCD.print(" 10K ");
    LCD.print(tenKIR);
  }
  while(digitalRead(49) == LOW){}
}


void irMenu()
{
  float rightTotal = 0;
  float leftTotal = 0;
  int maxCount = 20;
  while(digitalRead(49) == HIGH)
  {
    for(int count = 0; count<maxCount; count++)
    {
      rightTotal += analogRead(3);
      leftTotal += analogRead(2);
      delay(2);
    }
    float rightIR = rightTotal/maxCount;
    float leftIR = leftTotal/maxCount; 
    LCD.clear(); LCD.home();
    LCD.print("->IR correct ");
    LCD.print(rightSensorCorrection);
    LCD.setCursor(0,1);
    LCD.print("left ");
    LCD.print(leftIR);
    LCD.print(" right ");
    LCD.print(rightIR);
    if (digitalRead(50) == LOW) {
      while (digitalRead(50) == LOW) {}
      rightSensorCorrection = leftIR/rightIR;
    }
  }
  while(digitalRead(49) == LOW){}
}



void strategyMenu()
{
  while(digitalRead(49) == HIGH)
  {
    float angle = analogRead(6)/(1023.0/180.0);
    float angleBackarm = analogRead(7)/(1023.0/180.0);
    baseServo.write(angle);
    RCServo0.write(angleBackarm);
    RCServo1.write(180-angleBackarm);
    LCD.clear(); LCD.home();
    LCD.print(angle);
    LCD.setCursor(0,1);
    LCD.print(angleBackarm);
    delay(100);
  }
  while(digitalRead(49) == LOW){}
}

void setStrategy()
{
  
}


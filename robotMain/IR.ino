void irMenu()
{
  while(digitalRead(49) == HIGH)
  {
    float tenKIR = analogRead(5);
    float oneKIR = analogRead(4);
    LCD.clear(); LCD.home();
    LCD.print("1K ");
    LCD.print(oneKIR);
    LCD.setCursor(0,1);
    LCD.print(" 10K ");
    LCD.print(tenKIR);
  }
  while(digitalRead(49) == LOW){}
}


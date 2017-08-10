void readEncoders(){
  resetRotations();

  while(digitalRead(49)){
    LCD.clear(); LCD.home();
    LCD.print(left_rotations);
    LCD.setCursor(0, 1);
    LCD.print(right_rotations);
  }
}


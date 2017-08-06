void encoderTestor(){
  LCD.clear();LCD.home();
  LCD.print("SPIN THE WHEEL");

  LCD.setCursor(0, 1);
  while(digitalRead(49) == HIGH){
    LCD.clear();LCD.home();
    LCD.print("SPIN THE WHEEL");
    LCD.setCursor(0, 1);
    LCD.print(right_rotations);
    LCD.setCursor(7, 1);
    LCD.print(left_rotations);
    delay(50);

    if(digitalRead(50) == LOW){
      left_rotations = 0;
      right_rotations = 0;
    }
  }
}

//void readEncoder(){
//  int buttonON = digitalRead(50);
//  
//  while(buttonON == HIGH){
//    buttonON = digitalRead(50);
//    while(buttonON == LOW){
//      buttonON = digitalRead(50);
//      if(buttonON == HIGH) break;
//    }
//  }
//
//  while(digitalRead(49) == HIGH){
//    LCD.clear();LCD.home();
//    LCD.print(left_rotations);
//    delay(100);
//  }
//}


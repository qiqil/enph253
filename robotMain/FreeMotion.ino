//Encoder Based Movements

void stopMotors (){
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void driveStraight(unsigned long distance, int speed){
  left_rotations = 0;
  right_rotations = 0;
  int prev_control = 0;

  while(left_rotations + right_rotations < distance) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(left_rotations);
    LCD.setCursor(0, 1); LCD.print(right_rotations);
    int control = 0;
    if (left_rotations > right_rotations + 20) {
      control = 45;
    } else if (left_rotations < right_rotations - 20) {
      control = -45; 
    }
    if (control * prev_control > 0) {
      control = control + prev_control;
    }
    motor.speed(0, speed - control);
    motor.speed(1, speed + control);
    if (control > 0) {
      prev_control = 45;
    } else if (control < 0) {
      prev_control = -45;
    } else {
      prev_control = 0;
    }
  }

  stopMotors();
}

void reverse(unsigned long distance, int speed){
  
}

void brake(){
  
}


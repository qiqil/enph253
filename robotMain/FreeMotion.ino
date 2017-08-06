//Encoder Based Movements
int eKd = 0;
int eKp = 50;
int stepSize = 10;


void stopMotors (){
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void driveStraight(unsigned long distance, int speed){
  left_rotations = 0;
  right_rotations = 0;
  int prev_control = 0;
  int delta = 0;
  float netDelta = 0;
  float steps = 0;
  int I = 0;
  int control= 0;
  
  while(left_rotations <distance && right_rotations < distance) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(left_rotations);
    LCD.setCursor(0, 1); LCD.print(right_rotations);

    //trouble shooting POS
    char buffer [100];
    int output = sprintf(buffer, "Control is: %d, Integral is : %d", control, I);
    for(int i = 0; i <= output; i++){
      Serial.print(buffer[i]);
    }
    Serial.println("");
    
    control = 0;
    if (left_rotations > right_rotations + stepSize) {
      control = eKp ;
    } else if (left_rotations < right_rotations - stepSize) {
      control = -eKp; 
    }
    
//    netDelta += left_rotations - right_rotations;
//    I = netDelta/steps;
    
//    if(abs(I) > 60){
//      I = I/(abs(I)) * 60;  
//    }
    
//    control += I;

    control = -46; //its a stupid, workable solution, fuck.
    
    if (control * prev_control > 0) {
      control = control + prev_control;
    }
    motor.speed(0, speed + control);
    motor.speed(1, speed - control);
    if (control > 0) {
      prev_control = -60;
    } else if (control < 0) {
      prev_control = 60;
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


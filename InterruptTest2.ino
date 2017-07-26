
#include <phys253.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>
 
volatile unsigned int INT_0 = 0;
volatile unsigned int INT_1 = 0;
volatile unsigned int INT_2 = 0;
volatile unsigned int INT_3 = 0;
double rotation;
 
ISR(INT0_vect) {LCD.clear(); LCD.home(); LCD.print("INT0: "); LCD.print(INT_0++); rotation = (INT_0)/48;
LCD.print(" "); LCD.print(rotation);};
//ISR(INT1_vect) {LCD.clear(); LCD.home(); LCD.print("INT1: "); LCD.print(INT_1++);};
//ISR(INT2_vect) {LCD.clear(); LCD.home(); LCD.print("INT2: "); LCD.print(INT_2++);};
//ISR(INT3_vect) {LCD.clear(); LCD.home(); LCD.print("INT3: "); LCD.print(INT_3++);};
 
/*  Enables an external interrupt pin
INTX: Which interrupt should be configured?
    INT0    - will trigger ISR(INT0_vect)
    INT1    - will trigger ISR(INT1_vect)
    INT2    - will trigger ISR(INT2_vect)
    INT3    - will trigger ISR(INT3_vect)
mode: Which pin state should trigger the interrupt?
    LOW     - trigger whenever pin state is LOW
    FALLING - trigger when pin state changes from HIGH to LOW
    RISING  - trigger when pin state changes from LOW  to HIGH 
*/
void enableExternalInterrupt(unsigned int INTX, unsigned int mode)
{
  if (INTX > 3 || mode > 3 || mode == 1) return;
  cli();
  /* Allow pin to trigger interrupts        */
  EIMSK |= (1 << INTX);
  /* Clear the interrupt configuration bits */
  EICRA = ~(1 << (INTX*2+0));
  EICRA = ~(1 << (INTX*2+1));
  /* Set new interrupt configuration bits   */
  EICRA |= mode << (INTX*2);
  sei();
}
 
void disableExternalInterrupt(unsigned int INTX)
{
  if (INTX > 3) return;
  EIMSK = ~(1 << INTX);
}
 
void setup()
{
  #include <phys253setup.txt> 
  enableExternalInterrupt(INT0, FALLING);
  Serial.begin(9600);
}
 
void loop()
{
}

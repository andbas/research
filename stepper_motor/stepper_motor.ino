#include <Stepper.h>
#define STEPS 48
Stepper stepper(STEPS, 2, 3, 4, 5);
void setup(){
stepper.setSpeed(30);
}
void loop()
{
  stepper.step(1*STEPS);
  delay(1000);
  stepper.step(-1*STEPS);
  delay(1000);
}

#include <Servo.h> 
#include <Ultrasonic.h>

#define RIGHT_HAND_PIN    2
#define LEFT_HAND_PIN    3
#define HEAD_PIN       4

#define TRIGGER_PIN    7
#define ECHO_PIN       6


Servo rightHand; 
Servo leftHand;
Servo head;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

float cmMsec;
byte headAngle = 90;
byte leftHandAngle = 180;
byte rightHandAngle = 0;


void setup() {
  rightHand.attach(RIGHT_HAND_PIN);
  leftHand.attach(LEFT_HAND_PIN);
  head.attach(HEAD_PIN);
  rightHand.write(rightHandAngle);
  leftHand.write(leftHandAngle);
  head.write(headAngle);
} 
 
 
void loop() { 
  
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  if(cmMsec > 80){
    setServoAngle(RIGHT_HAND_PIN,0,200);
  }else if(cmMsec <= 80 && cmMsec > 20){
    waveHand(RIGHT_HAND_PIN);
  }else{
    shakeHead();
  }
}

void waveHand(byte handPinNumber){
  setServoAngle(handPinNumber,160,400);
  setServoAngle(handPinNumber,130,400);
}

void shakeHead(){
  byte headState = headAngle;
  for(byte i=0;i<3;i++){
    setServoAngle(HEAD_PIN, 40, 200);
    setServoAngle(HEAD_PIN, 140, 200);
  }
  setServoAngle(HEAD_PIN, headState, 500);
}

void setServoAngle(byte pinNumber, byte angle, int delayMs){
  switch(pinNumber){
    case RIGHT_HAND_PIN:
      rightHandAngle = angle;
      rightHand.write(rightHandAngle);
      break;
    case LEFT_HAND_PIN:
      leftHandAngle = 180 - angle;
      leftHand.write(leftHandAngle);
      break;
    case HEAD_PIN:
      headAngle = angle;
      head.write(headAngle);
      break;
  }
  delay(delayMs);
}

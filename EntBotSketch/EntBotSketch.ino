#include <Servo.h>
#include <Ultrasonic.h>

Servo head;
Ultrasonic ultrasonic(3,4);
boolean side = true;
boolean isTurn = false;

void setup() { 
  Serial.begin(9600);  
  Serial.println("setup in");  
  head.attach(2);
  digitalWrite(8, side?HIGH:LOW);
  digitalWrite(9, !side?HIGH:LOW);
  digitalWrite(10, !side?HIGH:LOW);
  digitalWrite(11, side?HIGH:LOW);
  analogWrite(6,150);
  analogWrite(7,150);  
  head.write(90);
}

float cmMsec;
void loop() {
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distance: ");
  Serial.println(cmMsec);
  if(cmMsec < 40){
    isTurn = true;
  }else{
    isTurn = false;
  }
  Serial.print("isTurn: ");
  Serial.println(isTurn);
  chooseDirection();
  delay(100);
}

void chooseDirection(){
  if(isTurn){
    digitalWrite(8, side?HIGH:LOW);
    digitalWrite(9, !side?HIGH:LOW);
    digitalWrite(10, !side?HIGH:LOW);
    digitalWrite(11, side?HIGH:LOW);  
  } else {
    digitalWrite(8, side?HIGH:LOW);
    digitalWrite(9, !side?HIGH:LOW);
    digitalWrite(10, side?HIGH:LOW);
    digitalWrite(11, !side?HIGH:LOW);  
  }
}

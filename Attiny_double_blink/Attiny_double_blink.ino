int led1 = 0;
int led2 = 1;

void setup() {                
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  analogWrite(led1,64);
  delay(500);
  analogWrite(led1,128);
  delay(500);
  analogWrite(led1,255);
  delay(500);
  digitalWrite(led1,LOW);
  
  analogWrite(led2,64);
  delay(500);
  analogWrite(led2,128);
  delay(500);
  analogWrite(led2,255);
  delay(500);
  digitalWrite(led2,LOW);
  
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  delay(500);
}

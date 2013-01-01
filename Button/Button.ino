byte led = 13;
byte echoPin = 2;

void setup() {                
  Serial.begin(9600);
}

void loop() {
  pulseIn(echoPin,HIGH);
  digitalWrite(led, HIGH);
  
  pulseIn(echoPin,LOW);
  digitalWrite(led, LOW);
}

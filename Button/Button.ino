int pin = 13;
int echoPin = 2;
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  attachInterrupt(0, blink, CHANGE);
}

void loop()
{
  digitalWrite(pin, state);
}

void blink()
{
  delay(1);
  if(digitalRead(echoPin)==HIGH){
    Serial.println("Real press");
  }else if(!state){
    Serial.println("Fake");    
  }
  state = !state;
  delay(10);
}

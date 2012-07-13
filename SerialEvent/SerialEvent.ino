boolean stringComplete = false;
byte power = 0;
boolean side = true;
boolean isTurn = false;

void setup() {
  Serial.begin(9600);  
  Serial.println("setup in");
  digitalWrite(8, side?HIGH:LOW);
  digitalWrite(9, !side?HIGH:LOW);
  digitalWrite(10, side?HIGH:LOW);
  digitalWrite(11, !side?HIGH:LOW);  
}

void loop() {
  if (stringComplete) {
    chooseDirection();
    analogWrite(6,power);
    analogWrite(7,power);
    power = 0;
    stringComplete = false;
  }
}

void serialEvent() {
 
  while (Serial.available()) {
    byte inChar = (byte)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    }else if (inChar == '-'){
      side = !side;
    } else if(inChar == '+'){
      isTurn = !isTurn;
    } else {
      power = power * 10 + (inChar - (byte)'0');
    }
  }
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





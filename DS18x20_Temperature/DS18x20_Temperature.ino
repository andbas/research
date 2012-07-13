#include <OneWire.h>

byte wirePin = 8;

OneWire ds(wirePin);  

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  byte addr[8];

  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  byte i;
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  Serial.println();
  
  if (addr[0] == 0x28){
    Serial.println("  Chip = DS18B20");
  }else {
    Serial.println("Device is not a DS18B20 chip");
    return;
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44);

  while(digitalRead(wirePin) == 0){
    delay(50);
  }
  
  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);

  byte data[9];
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  unsigned int raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw << 3;
  else if (cfg == 0x20) raw = raw << 2;
  else if (cfg == 0x40) raw = raw << 1;
  
  float celsius, fahrenheit;
  
  
  
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
}

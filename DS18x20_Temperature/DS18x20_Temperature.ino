#include <OneWire.h>

byte wirePin = 8;

OneWire  ds(wirePin);

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
 
  if (addr[0]==0x10){
    Serial.println("  Chip = DS18S20");
  } else {
    Serial.println("Device is not a DS18S20.");
    return;
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44);        
  
  delay(750);

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);     
  
  byte data[9];
  Serial.print("  Data = ");
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  
  if (OneWire::crc8(data, 8) != data[8]) {
      Serial.println("Data CRC is not valid!");
      return;
  }
  
  int16_t raw = (((int16_t)data[1]) << 8) | data[0];
  
  float celsius, fahrenheit;
  celsius = (float)(raw >> 1) - 0.25 + 
            ((float)(data[7] - data[6]) / (float)data[7] );
  fahrenheit = celsius * 1.8 + 32.0;
  
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
}
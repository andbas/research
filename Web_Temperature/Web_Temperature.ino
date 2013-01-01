#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>

// Ethernet Configuration
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// Used default port for HTTP
EthernetServer server(80);
IPAddress ip(192,168,0,33);


//Buffer for messages

byte wirePin = 8;
OneWire ds(wirePin);
byte addr[8];

byte ledPin = 7;
boolean isLedOn = false;

unsigned long lastUpdate = 0;

float temperature = -100.0;


void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Ethernet.begin(mac,ip);
  server.begin();
  connectToSensor();
}

void loop(void) {
  updateTemperature();

  EthernetClient client = server.available();

  if(client){

    String request;

    boolean currentLineIsBlank = true;
    boolean requestLineReceived = false;

    while(client.connected()){
      if (client.available()) {
        char c = client.read();

        if(c == '\n' && currentLineIsBlank) { 
          // substract path from a request line
          request = request.substring( request.indexOf(' ') + 1 , request.lastIndexOf(' '));
          if(request=="/"){
            successHeader(client);
            generatePage(client);
          }
          else if(request=="/switch-on"){
            digitalWrite(ledPin, HIGH);
            isLedOn = true;
            redirectHeader(client, "/");
          }
          else if(request=="/switch-off"){
            digitalWrite(ledPin, LOW);
            isLedOn = false;
            redirectHeader(client, "/");
          }
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
          if(!requestLineReceived){
            requestLineReceived = true;
          }
        } 
        else if (c != '\r') {
          if(!requestLineReceived) {
            request += c;
          }
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }  
}

void successHeader(EthernetClient client){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
}

void redirectHeader(EthernetClient client, String path){
  client.println("HTTP/1.1 302 Moved Temporarily");
  client.println("Content-Type: text/html");
  client.println("Location: " + path);
  client.println("Connnection: keep-alive");
  client.println();
}

void generatePage(EthernetClient client){
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("  <title>Server</title>");
  client.println("</head>");

  client.println("<body>");
  String ledStatus = isLedOn ? "ON" : "OFF";
  client.println("  <h1>Led is " + ledStatus + "</h1>");

  if(temperature != -100.0){
    client.println("  <h1>Temperature is " + floatToString(temperature, 100) + "</h1>");
  }
  client.println("  <a href=\"/switch-on\">Switch ON</a>");
  client.println("  <br />");
  client.println("  <a href=\"/switch-off\">Switch OFF</a>");
  client.println("</body>");
  client.println("</html>");
}

String floatToString(float value, byte precision){
  int intVal = int(value);
  unsigned int frac;
  if(intVal >= 0){
    frac = (value - intVal) * precision;
  } 
  else {
    frac = (intVal - value) * precision;
  }
  return String(intVal) + "." + String(frac);
}

void updateTemperature(){
  unsigned long time = millis();
  if((time - lastUpdate) > 5000 || lastUpdate == -100.0){
    lastUpdate = time;
    temperature = getTemperature();
    Serial.println(floatToString(temperature,100));
  }
}

float getTemperature() {

  ds.reset();
  ds.select(addr);
  ds.write(0x44);        

  delay(750);

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);     

  byte data[9], i;
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  if (OneWire::crc8(data, 8) != data[8]) {
    return temperature;
  }

  unsigned int raw = (data[1] << 8) | data[0];
  raw = raw << 3;
  if (data[7] == 0x10) {
    raw = (raw & 0xFFF0) + 12 - data[6];
  }

  float celsius;
  celsius = (float)raw / 16.0;
  return celsius;
}

void connectToSensor(){
  if ( !ds.search(addr) || OneWire::crc8(addr, 7) != addr[7] || addr[0]!=0x10) {
    ds.reset_search();
    delay(250);
    connectToSensor();
  }
}


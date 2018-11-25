#include "SoftwareSerial.h"
SoftwareSerial SerialESP(2, 3); // RX, TX
 
const int baudRate = 9600;
String request;
 
void setup(){
   Serial.begin(baudRate);
   SerialESP.begin(baudRate);
   delay(1000);
   Serial.println("Start from the Arduino");
}
 
void loop(){
  while(!SerialESP.available());
  request = SerialESP.readString();
  Serial.println(request);
  SerialESP.println(request);
}

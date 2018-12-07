#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DEBUG false
//SSID and Password of your WiFi router
const char* ssid = "ESP8266";
const char* password = "12345678";
int respond = 0;
String response;

ESP8266WebServer server(80); //Server on port 80

void execute(String operacion){
  Serial.println(operacion);
  respond = 0;
  for(int i = 0; i<50 && !respond; i++){
    if(Serial.available()){
      response = Serial.readString();
      respond = 1;
    }else{
      delay(100);
    }
  }
  if(respond){
    server.send(200, "text/plain", response);
  }else{
    server.send(200, "text/plain", "500 ERROR: TIMEOUT");

    //Para evitar desincronizacion con el Arduino
    while(!Serial.available());
    response = Serial.readString();
  }
  return;
}

//===============================================================
//     This rutine is exicuted when you open its IP in browser
//===============================================================
void handleRoot(){ server.send(200, "text/plain", "OK"); }
void handleStatus(){ execute("STATUS"); }
void handleStop(){ execute("STOP"); }
void handleFilter(){ execute("FILTER"); }
void handleWash(){ execute("WASH"); }
void handleRinse(){ execute("RINSE"); }
void handleDrain(){ execute("DRAIN"); }

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  delay(1000);
  Serial.begin(9600);
  if(DEBUG){ Serial.println(); }
  if(DEBUG){ Serial.println("Comienzo del Programa"); }

  //Configuración del ESP8266 en modo AccessPoint
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();

  
  if(DEBUG){ Serial.print("IP address: "); }
  Serial.println(myIP); //IP address assigned to your ESP

  
  server.on("/ping", handleRoot);
  server.on("/status", handleStatus);
  server.on("/stop", handleStop);
  server.on("/filter", handleFilter);
  server.on("/wash", handleWash);
  server.on("/rinse", handleRinse);
  server.on("/drain", handleDrain);
  
  server.begin(); //Start server

  
  if(DEBUG){ Serial.println("Diagnóstico: "); }
  if(DEBUG){ WiFi.printDiag(Serial); }
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}

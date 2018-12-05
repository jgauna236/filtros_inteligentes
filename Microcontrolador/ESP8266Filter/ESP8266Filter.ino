#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DEBUG false
//SSID and Password of your WiFi router
const char* ssid = "Telecentro-1a10";
const char* password = "FGZJRDN3UZYY";
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
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(DEBUG){ Serial.println(""); }

    // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if(DEBUG){ Serial.print("."); }
  }

  //If connection successful show IP address in serial monitor
  if(DEBUG){ Serial.println(""); }
  if(DEBUG){ Serial.print("Connected to "); }
  if(DEBUG){ Serial.println(ssid); }
  if(DEBUG){ Serial.print("IP address: "); }
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  
  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/stop", handleStop);
  server.on("/filter", handleFilter);
  server.on("/wash", handleWash);
  server.on("/rinse", handleWash);
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

/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define DEBUG false
//SSID and Password of your WiFi router
const char* ssid = "AndroidAP";
const char* password = "12345678";
String response;

ESP8266WebServer server(80); //Server on port 80

void execute(String operacion){
  if(DEBUG){Serial.println("START");}
  Serial.println(operacion);
  while(!Serial.available());
  response = Serial.readString();

  if(DEBUG){Serial.println(response);}
  if(DEBUG){Serial.println("Send response");}
  server.send(200, "text/plain", response);
  if(DEBUG){Serial.println("END");}
  return;
}

//===============================================================
//     This rutine is exicuted when you open its IP in browser
//===============================================================
void handleRoot(){ server.send(200, "text/plain", "OK"); }
void handleStatus(){ execute("STATUS"); }
void handleFilter(){ execute("FILTER"); }
void handleWash(){ execute("WASH"); }
void handleStop(){ execute("STOP"); }
void handleDrain(){ execute("DRAIN"); }
void handleLoad(){ execute("LOAD"); }

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);//Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);
  server.on("/stop", handleStop);
  server.on("/load", handleLoad);
  server.on("/status", handleStatus);
  server.on("/filter", handleFilter);
  server.on("/wash", handleWash);
  server.on("/drain", handleDrain);

  server.begin();//Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}

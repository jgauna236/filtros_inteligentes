#include "SoftwareSerial.h"
#include "FilterConst.h"


//Defino las tareas que se van a utilizar
void configPines();
void wait_requests(void *pvParameters);
void watchdog(void *pvParameters);

SoftwareSerial SerialESP(2, 3); // RX, TX
String request, response;
int state = STOP;
int sensor_pool, sensor_glass;
 
void setup(){
  Serial.begin(BAUD_RATE);
  SerialESP.begin(BAUD_RATE);
  configPines();
  Serial.println("Wait ESP8266");
  while(!SerialESP.available());
  Serial.println(SerialESP.readString());
}

void loop(){
  if(SerialESP.available()){
    request = SerialESP.readString();
    if(request.substring(0,6) == "STATUS"){
      Serial.println("STATUS");
      response = response_status();
    }else if(request.substring(0,4) == "STOP"){
      Serial.println("STOP");
      response = response_stop();
    }else if(request.substring(0,6) == "FILTER"){
      Serial.println("FILTER");
      response = response_filter();
    }else if(request.substring(0,4) == "WASH"){
      Serial.println("WASH");
      response = response_wash();
    }else if(request.substring(0,5) == "RINSE"){
      Serial.println("RINSE");
      response = response_rinse();
    }else if(request.substring(0,5) == "DRAIN"){
      Serial.println("DRAIN");
      response = response_drain();
    }else{
      response = "ERROR: OPERACION DESCONOCIDA";
    }
    if(DEBUG){ Serial.println(response); }
    SerialESP.println(response);
  }
  watchdog();
}

void configPines(){
  //Válvulas
  pinMode(VALVE_1, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_5, OUTPUT);
  //Motor
  pinMode(MOTOR,   OUTPUT);
  //Sensores
  pinMode(SENSOR_POOL,  INPUT);
  pinMode(SENSOR_GLASS, INPUT);
}

String response_status(){
  sensor_pool   = digitalRead(SENSOR_POOL);
  sensor_glass  = digitalRead(SENSOR_GLASS);
  response = "" + String(state) + String(sensor_pool) + String(sensor_glass) + " - ";
  switch(state){
  case STOP:
    response += "STATUS: STOP - ";
  break;
  case FILTER:
    response += "STATUS: FILTER - ";
  break;
  case WASH:
    response += "STATUS: WASH - ";
  break;
  case RINSE:    
    response += "STATUS: RINSE - ";
  break;
  case DRAIN:
    response += "STATUS: DRAIN - ";
  break;
  }
  if(sensor_pool){ response += "PILETA CON AGUA - "; }
  else{ response += "PILETA SIN AGUA - "; }
  if(sensor_glass){ response += "VASO CON AGUA"; }
  else{ response += "VASO SIN AGUA"; }
  
  return response;
}

String response_stop(){
  digitalWrite(MOTOR,   LOW);
  digitalWrite(VALVE_1, LOW);
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_3, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_5, LOW);
  return "SUCCESS";  
}

String response_filter(){
  switch (state) {
  case STOP:
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass || DEBUG){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, HIGH);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "SUCCESS";
    }else{
      return "ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "ERROR: DESCONOCIDO";
  }
}

String response_wash(){
  switch (state) {
  case STOP:
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass || DEBUG){
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, HIGH);
      digitalWrite(VALVE_3, HIGH);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "SUCCESS";
    }else{
      return "ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "ERROR: DESCONOCIDO";
  }
}

String response_rinse(){
  switch (state) {
  case STOP:
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass || DEBUG){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, HIGH);
      digitalWrite(MOTOR, HIGH);
      return "SUCCESS";
    }else{
      return "ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "ERROR: DESCONOCIDO";
  }
}

String response_drain(){
  switch (state) {
  case STOP:
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass || DEBUG){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, HIGH);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "SUCCESS";
    }else{
      return "ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "ERROR: DESCONOCIDO";
  }
}

void watchdog(){
  sensor_pool   = digitalRead(SENSOR_POOL);
  sensor_glass  = digitalRead(SENSOR_GLASS);
  if(!sensor_pool || !sensor_glass){
    /*
    digitalWrite(MOTOR,   LOW);
    digitalWrite(VALVE_1, LOW);
    digitalWrite(VALVE_2, LOW);
    digitalWrite(VALVE_3, LOW);
    digitalWrite(VALVE_4, LOW);
    digitalWrite(VALVE_5, LOW);
    state = STOP; 
    */ 
  }
}

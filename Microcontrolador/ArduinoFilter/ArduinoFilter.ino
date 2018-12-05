#include "SoftwareSerial.h"
#include "FilterConst.h"


//Defino las tareas que se van a utilizar
void configPines();
void wait_requests(void *pvParameters);
void watchdog(void *pvParameters);

SoftwareSerial SerialESP(3, 2); // TX, RX
String request, response;
int state = STOP;
int sensor_pool, sensor_glass;
 
void setup(){
  Serial.begin(BAUD_RATE);
  SerialESP.begin(BAUD_RATE);
  configPines();


  // Rinicia el Módulo ESP8266
  digitalWrite(RESET, LOW);
  delay(1000);
  digitalWrite(RESET, HIGH);
  delay(1000);
  SerialESP.readString(); //Lee basura que llega desde el ESP8266 al reiniciarse

  //Obtengo la IP del ESP8266, para imprimirla en pantalla.
  Serial.println("Wait ESP8266");
  while(!SerialESP.available());
  Serial.print("IP del ESP8266: ");
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

  pinMode(RESET, OUTPUT);
}

String response_status(){
  sensor_pool   = digitalRead(SENSOR_POOL);
  sensor_glass  = digitalRead(SENSOR_GLASS);

  switch(state){
  case STOP:
    if(sensor_pool && sensor_glass){
      response = "00 STOP";
    } else if(sensor_pool && !sensor_glass){
      response = "01 STOP";
    } else if(!sensor_pool && sensor_glass){
      response = "02 STOP";
    } else {
      response = "03 STOP";
    }
  break;
  case FILTER:
    if(sensor_pool && sensor_glass){
      response = "10 FILTER";
    } else if(sensor_pool && !sensor_glass){
      response = "11 FILTER";
    } else if(!sensor_pool && sensor_glass){
      response = "12 FILTER";
    } else {
      response = "13 FILTER";
    }
  break;
  case WASH:
    if(sensor_pool && sensor_glass){
      response = "20 WASH";
    } else if(sensor_pool && !sensor_glass){
      response = "21 WASH";
    } else if(!sensor_pool && sensor_glass){
      response = "22 WASH";
    } else {
      response = "23 WASH";
    }
  break;
  case RINSE:    
    if(sensor_pool && sensor_glass){
      response = "30 RINSE";
    } else if(sensor_pool && !sensor_glass){
      response = "31 RINSE";
    } else if(!sensor_pool && sensor_glass){
      response = "32 RINSE";
    } else {
      response = "33 RINSE";
    }
  break;
  case DRAIN:
    if(sensor_pool && sensor_glass){
      response = "40 DRAIN";
    } else if(sensor_pool && !sensor_glass){
      response = "41 DRAIN";
    } else if(!sensor_pool && sensor_glass){
      response = "42 DRAIN";
    } else {
      response = "43 DRAIN";
    }
  break;
  }

  return response;
}

String response_stop(){
  state = STOP;
  digitalWrite(MOTOR,   LOW);
  digitalWrite(VALVE_1, LOW);
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_3, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_5, LOW);
  return "200 SUCCESS";  
}

String response_filter(){
  switch (state) {
  case STOP:
    state         = FILTER;
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, HIGH);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "200 SUCCESS";
    }else{
      return "300 ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "400 ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "404 ERROR: DESCONOCIDO";
  }
}

String response_wash(){
  switch (state) {
  case STOP:
    state         = WASH;
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass){
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, HIGH);
      digitalWrite(VALVE_3, HIGH);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "200 SUCCESS";
    }else{
      return "300 ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "400 ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "404 ERROR: DESCONOCIDO";
  }
}

String response_rinse(){
  switch (state) {
  case STOP:
    state         = RINSE;
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, HIGH);
      digitalWrite(MOTOR, HIGH);
      return "200 SUCCESS";
    }else{
      return "300 ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "400 ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "404 ERROR: DESCONOCIDO";
  }
}

String response_drain(){
  switch (state) {
  case STOP:
    state         = DRAIN;
    sensor_pool   = digitalRead(SENSOR_POOL);
    sensor_glass  = digitalRead(SENSOR_GLASS);
    if(sensor_pool && sensor_glass){
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, HIGH);
      digitalWrite(VALVE_3, LOW);
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_5, LOW);
      digitalWrite(MOTOR, HIGH);
      return "200 SUCCESS";
    }else{
      return "300 ERROR: PILETA O VASO SIN AGUA";
    }
  break;
  case FILTER: case WASH: case RINSE: case LOAD: case DRAIN:
    return "400 ERROR: OPERACION EN PROCESO";
  break;
  default:
    return "404 ERROR: DESCONOCIDO";
  }
}

void watchdog(){
  sensor_pool   = digitalRead(SENSOR_POOL);
  sensor_glass  = digitalRead(SENSOR_GLASS);
  if(!sensor_pool || !sensor_glass){
    state = STOP; 
    digitalWrite(MOTOR,   LOW);
    digitalWrite(VALVE_1, LOW);
    digitalWrite(VALVE_2, LOW);
    digitalWrite(VALVE_3, LOW);
    digitalWrite(VALVE_4, LOW);
    digitalWrite(VALVE_5, LOW);
  }
}

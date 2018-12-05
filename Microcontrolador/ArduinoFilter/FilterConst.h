#ifndef FILTER_CONST_FILE
  #define FILTER_CONST_FILE

  //Pines Semáforos
  #define VALVE_1  8
  #define VALVE_2  9
  #define VALVE_3  10
  #define VALVE_4  11
  #define VALVE_5  12
  #define MOTOR    13
  
  //Sensores de Líquidos
  #define SENSOR_POOL  A0
  #define SENSOR_GLASS A1

  //Reset del ESP8266
  #define RESET A2

  //ESTADOS
  #define STOP    0
  #define FILTER  1
  #define WASH    2
  #define RINSE   3
  #define LOAD    4
  #define DRAIN   5

  //Velocidad del Serial
  #define BAUD_RATE 9600

  #define DEBUG true
#endif



#define FIREBASE_HOST "https://filtros-inteligentes.firebaseio.com/"
#define FIREBASE_AUTH "IeTB4YQeuVY0dFCyRD2cW5nI7jIMq6p4odKyYZBG"
#define WIFI_SSID "Gauna"
#define WIFI_PASSWORD "monokilo123"
#define RELE 2
 
void setup() {
    pinMode(RELE,OUTPUT);
    digitalWrite(RELE,0);
    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("conectado: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.setInt("LEDStatus",0);
}

void loop() {
    if(Firebase.getInt("LEDStatus")){
        digitalWrite(RELE,HIGH);
    }else{
        digitalWrite(RELE,LOW);
    }
    // Check for errors
    if (Firebase.failed()) {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
    }
    delay(1000);

}
// /***   Setup  ***/
// void setup() {
//     pinMode(rele,OUTPUT);
// }
 
// /***   Loop  ***/
// void loop() {
//     delay(1000);
//     digitalWrite(rele, HIGH);
//     delay(1000);
//     digitalWrite(rele, LOW);

// }

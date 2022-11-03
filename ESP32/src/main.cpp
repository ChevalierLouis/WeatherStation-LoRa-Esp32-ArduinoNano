#include <Arduino.h>
#include "wificonfig.h"
#include "server.h"
#include "loraRecever.h"



// fonction initialisation SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("erreur SPIFFS");
  }
  Serial.println("pas d'erreur SPIFFS");
}

void setup() {
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());
  //initialisation SPIFFS
  initSPIFFS();
  //lecture de la config
  readConf();
  //si l'esp se connecte a un reseau WIFI 
  if(initWiFi()) {
    handleRoot();//page principale
  }
  else {
    wifiManager();//gestionaire du wifi 
   }
   setup_LoRa();
}
void loop() {
loop_LoRa();
}
#include "loraRecever.h"
#define ss 5
#define rst 14
#define dio0 2
int LoRaRSSI;

String temp;
String hum;
String speed;

void setup_LoRa(void){
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0x39);
  Serial.println(" initialisation LoRa OK!");
}
void loop_LoRa(void){
int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Serial.print("Received packet '");
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      //Serial.println(LoRaData);
      if (LoRaData.startsWith("sM")){
      int d = 2;
      int f = LoRaData.indexOf(',', d);   
      temp = LoRaData.substring(d, f);
      
      d = f + 1;
      f = LoRaData.indexOf(',', d);
      hum = LoRaData.substring(d, f);
      
      d = f + 1;
      f = LoRaData.indexOf(',', d);
      speed = LoRaData.substring(d, f);
      }

    }
    LoRaRSSI=LoRa.packetRssi();
  }
}
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

String out;

void setup() {
  Serial.begin(9600);
  dht.begin();
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0x39);
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("sM"+String(dht.readTemperature())+","+String(dht.readHumidity())+","+String(map(analogRead(A0),0,1023,0,250)));
  LoRa.endPacket();
  delay(1000);
}

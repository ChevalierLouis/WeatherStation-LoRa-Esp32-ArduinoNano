#include "server.h"
extern AsyncWebServer server;
extern int LoRaRSSI;

extern String temp;
extern String hum;
extern String speed;

//gestion de la page princpale
void handleRoot(void) {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(SPIFFS, "/style.css", "text/css");
  });

    server.on("/style1.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(SPIFFS, "/style1.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(SPIFFS, "/script.js", "text/javascript");
  });

  server.on("/val1", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(200, "text/plain", temp);
  });

  server.on("/val2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(200, "text/plain", hum);
  });
    server.on("/val3", HTTP_GET, [](AsyncWebServerRequest * request) {
    request -> send(200, "text/plain", speed);
  });
      server.on("/val4", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value4= String(LoRaRSSI) ;
    request -> send(200, "text/plain", value4);
  });
      server.on("/val5", HTTP_GET, [](AsyncWebServerRequest * request) {
    long int WifiRssi = WiFi.RSSI();
    String value5= String(WifiRssi) ;
    request -> send(200, "text/plain", value5);
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("LED LOW");
    request -> send(200);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("LED HIGH");
    request -> send(200);
  });

  server.begin();
  Serial.println("Serveur actif!");
}


#ifndef SERVEUR_H
#define SERVEUR_H
#include <Arduino.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
void handleRoot(void);
void serverBegin(void);
#endif
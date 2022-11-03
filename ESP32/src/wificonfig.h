#ifndef WIFICONFIG_H
#define WIFICONFIG_H
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <string.h>
bool initWiFi();
String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void readConf();
void wifiManager();
#endif
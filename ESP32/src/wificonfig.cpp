#include "wificonfig.h"
AsyncWebServer server(80);

//pour chercher les elements dans un methode POST
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
// const char* PARAM_INPUT_3 = "ip";
// const char* PARAM_INPUT_4 = "gateway";

//Variables pour sauvgarde les parametres 
String ssid;
String pass;
String ip;
String gateway;

//nom des fichier pour sauvgarder
const char* ssidPath = "/ssid.txt"; 
const char* passPath = "/pass.txt";
// const char* ipPath = "/ip.txt";
// const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 20); // hardcoded

// Set your Gateway IP address
//IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

//intervale pour laisser le temps a la conection WiFi
unsigned long previousMillis = 0;
const long interval = 10000;  

String transitionPage = "";

// initialisation WiFi
bool initWiFi(void) {
  if(ssid == "" || pass == ""){
    Serial.println("les champs ne sont pas remplis.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  //localIP.fromString(ip.c_str());
  //localGateway.fromString(gateway.c_str());

  // if (!WiFi.config(localIP)){
  //   Serial.println("Erreure STA");
  //   return false;
  // }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("connection au WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("erreure de connection.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

//ecriture dans les fichiers 
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("ecriture dans: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- erreure d'ecriture");
    return;
  }
  if(file.print(message)){
    Serial.println("- OK");
  } else {
    Serial.println("- pas OK");
  }
}
//lecture des fichiers
String readFile(fs::FS &fs, const char * path){
  Serial.printf("lecture dans: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- erreure de lecture");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}
void readConf(){
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  // ip = readFile(SPIFFS, ipPath);
  // gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  // Serial.println(ip);
  // Serial.println(gateway);
}
void wifiManager(){
    Serial.println("point d'acces");
    //creation d'un point d'acces
    WiFi.softAP("StationMétéo", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP adresse: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", SPIFFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID: ");
            Serial.println(ssid);
            // sauvegarde
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Mot de passe: ");
            Serial.println(pass);
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // if (p->name() == PARAM_INPUT_3) {
          //   ip = p->value().c_str();
          //   Serial.print("Adresse IP: ");
          //   Serial.println(ip);
          //   writeFile(SPIFFS, ipPath, ip.c_str());
          // }
          // if (p->name() == PARAM_INPUT_4) {
          //   gateway = p->value().c_str();
          //   Serial.print("Passerelle: ");
          //   Serial.println(gateway);
          //   writeFile(SPIFFS, gatewayPath, gateway.c_str());
          // }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      transitionPage="Redémarrage de l'ESP,vous pouvez connecter au resait Wi-Fi que vous avez configuré précédemment";
      request->send(200, "text/html", transitionPage);
      delay(1000);
      ESP.restart();
    });
    server.begin();
}
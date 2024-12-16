// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());


  server.on("", HTTP_GET, [](AsyncWebServerRequest *request) {
    
  });

  server.on("/digitalWrite/2/0", HTTP_POST, [](AsyncWebServerRequest *request) {
    
  });
  
  server.begin();
}

void loop(){};
// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");

  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.on("/digitalRead", HTTP_POST, [](AsyncWebServerRequest *req) {
    Serial.println("post");
    req->send(200, "application/json", "{\"idk\":\"2\"}");
  });

  pinMode(5, OUTPUT);

  server.begin();
}

void loop() {};
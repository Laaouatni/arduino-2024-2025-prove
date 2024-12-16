#include <ESPAsyncWebServer.h>
#include <WiFi.h>

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");

  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  server.on("/digitalRead", HTTP_POST, [](AsyncWebServerRequest *req) {
    req->send(HTTP_CODE_OK, "application/json", "ciao");
  });

  pinMode(5, OUTPUT);
}

void loop() {};
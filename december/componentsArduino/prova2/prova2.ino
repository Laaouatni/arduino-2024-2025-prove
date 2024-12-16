// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);

struct UsablePins {
  const int outputs[]  = {2,4,5,18,19,21,22,23,13,12,14,27,26,25,33,32};
  const int inputs[]   = {15,2,4,13,12,14,27,26,25};
} usablePins;

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");

  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.on("/digitalWrite", HTTP_POST, [](AsyncWebServerRequest *req) {
    const String receivedString = req->getParam("body", true)->value();
    JsonDocument receivedStringToJson;
    DeserializationError error = deserializeJson(receivedStringToJson, receivedString);
    if (error) return;
    digitalWrite(receivedStringToJson["id"], receivedStringToJson["value"]);
    JsonDocument jsonResponse;
    for(auto thisPinId : usablePins.outputs) {
      jsonResponse[thisPin] = digitalRead(thisPin);
    };
    String jsonResponseToString;
    serializeJson(jsonResponse, jsonResponseToString);
    req->send(200, "application/json", jsonResponseToString);
  });

  pinMode(5, OUTPUT);

  server.begin();
}

void loop() {};
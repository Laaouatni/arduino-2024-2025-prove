// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);

struct UsablePins {
  const int outputs[16]  = {2,4,5,18,19,21,22,23,13,12,14,27,26,25,33,32};
  const int inputs[9]   = {15,2,4,13,12,14,27,26,25};
} usablePins;

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");

  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  // Serial.print("0. before server on");
  // server.on("/digitalWrite", HTTP_POST, [](AsyncWebServerRequest *req) {
  //   Serial.print("1. server on");
  //   const String receivedString = req->getParam("body", true)->value();
  //   Serial.print("2. body value");
  //   JsonDocument receivedStringToJson;
  //   DeserializationError error = deserializeJson(receivedStringToJson, receivedString);
  //   Serial.print("3. before if error");
  //   if (error) return;
  //   Serial.print("4. after if error");

  //   pinMode(receivedStringToJson["id"], OUTPUT);
  //   digitalWrite(receivedStringToJson["id"], receivedStringToJson["value"]);
  //   Serial.print("5. pinMode/digital");

  //   JsonDocument jsonResponse;
  //   Serial.print("6. before Loop");
  //   for(auto thisOutputPinId : usablePins.outputs) {
  //     jsonResponse[thisOutputPinId] = digitalRead(thisOutputPinId);
  //   };
  //   Serial.print("6. after Loop");
  //   String jsonResponseToString;
  //   Serial.print("7. before serialize");
  //   serializeJson(jsonResponse, jsonResponseToString);
  //   Serial.print("8. after serialize");

  //   Serial.print("9. before send");
  //   req->send(200, "application/json", jsonResponseToString);
  //   Serial.print("10. after send CONGRATS");
  // });

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam("message", true)) {
            message = request->getParam("message", true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

  server.begin();
}

void loop() {};
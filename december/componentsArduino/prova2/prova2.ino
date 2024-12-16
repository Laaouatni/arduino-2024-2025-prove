// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);

struct UsablePins {
  const int outputs[16] = { 2, 4, 5, 18, 19, 21, 22, 23, 13, 12, 14, 27, 26, 25, 33, 32 };
  const int inputs[9] = { 15, 2, 4, 13, 12, 14, 27, 26, 25 };
} usablePins;

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");

  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.on("/digitalWrite/2/1", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Get path variables
    String pin = "2";
    String value = "1";

    // Convert pin and value to integers
    int pinNumber = pin.toInt();
    int pinValue = value.toInt();

    // Set the pin mode and perform digitalWrite
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, pinValue);

    // Respond back with the action
    String response = "Pin " + String(pinNumber) + " set to " + String(pinValue);
    request->send(200, "text/plain", response);
  });

  server.on("/digitalWrite/2/0", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Get path variables
    String pin = "2";
    String value = "0";

    // Convert pin and value to integers
    int pinNumber = pin.toInt();
    int pinValue = value.toInt();

    // Set the pin mode and perform digitalWrite
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, pinValue);

    // Respond back with the action
    String response = "Pin " + String(pinNumber) + " set to " + String(pinValue);
    request->send(200, "text/plain", response);
  });
  
  server.begin();
}

void loop(){};
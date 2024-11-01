#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  WiFi.begin("nomeWifi", "passwordWifi");
}

void loop() {
  WiFiClient myWifiClient;
  HTTPClient myHttpClient;

  myHttpClient.begin(myWifiClient, "http://192.168.129.201/api");
  
  int httpCode = myHttpClient.GET();

  if(httpCode > 0) {
    String payload = myHttpClient.getString();

    JsonDocument doc;
    deserializeJson(doc, payload);

    String receivedText = doc["hello"];
    Serial.println("✅" + String(receivedText));
  } else {
    Serial.println("❌❌❌" + String(httpCode) + "wifiStatus" + String(WiFi.status()));
  }

  myHttpClient.end();
};
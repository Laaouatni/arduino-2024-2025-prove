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

  myHttpClient.begin(myWifiClient, "http://ip.jsontest.com/");
  
  int httpCode = myHttpClient.GET();
  if(WiFi.status()==WL_CONNECTED) {
    if(httpCode > 0) {
      String payload = myHttpClient.getString();

      JsonDocument doc;
      deserializeJson(doc, payload);

      String receivedText = doc["ip"];
      Serial.println("✅ BRO " + String(receivedText));
    } else {
      Serial.println("❌❌❌" + String(httpCode) + "BRO wifiStatus" + String(WiFi.status()));
    }
    
    myHttpClient.end();
  }
};
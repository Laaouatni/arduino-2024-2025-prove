#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  WiFi.begin("nomeWifi", "passwordWifi");
}

void loop() {
  
};
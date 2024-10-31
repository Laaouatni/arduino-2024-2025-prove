#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  WiFi  .begin("nomeWifi", "passwordWifi");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){delay(500);Serial.print(".");}

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
}

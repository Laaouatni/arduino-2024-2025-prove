#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  WiFi.begin("nomeWifi", "passwordWifi");

  const int myLocalIp = Wifi.localIP;
}

void loop() {
  // i++;
  // Serial.println("abcd nonlosoome stai? aa " + String(i));
  // delay(1000);
};
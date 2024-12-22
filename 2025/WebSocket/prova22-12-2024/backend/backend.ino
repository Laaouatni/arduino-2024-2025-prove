#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
}

void loop() {};
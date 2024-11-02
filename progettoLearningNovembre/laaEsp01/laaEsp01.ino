#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "nomeWifi";
const char* password = "passwordWifi";

const char* htmlContent = "<html><body><h1>Hello, World!</h1></body></html>";

WiFiServer myServer(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED);

  myServer.begin();
}

void loop() {
  WiFiClient client = myServer.accept();
  if (!client) return;

  client.readStringUntil('\r');
  client.print(htmlContent);
  client.flush();
  client.stop();
};
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "nomeWifi";
const char* password = "passwordWifi";

const char* htmlContent = "<html><body><h1>Hello, World!</h1></body></html>";
  WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  // Create a web server on port 80
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);


  String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  client.print(header);
  client.print(htmlContent);

  client.stop();
}
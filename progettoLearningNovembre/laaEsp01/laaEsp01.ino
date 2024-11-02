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

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);


  String header = "";
  client.print(header);
  client.print(htmlContent);
  client.flush(); // Ensure data is sent

  client.stop();

  // Optional: Delay to avoid overloading the ESP8266
  delay(100);
}
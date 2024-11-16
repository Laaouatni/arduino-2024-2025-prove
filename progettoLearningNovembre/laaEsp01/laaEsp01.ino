// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>

// const char* ssid = "nomeWifi";
// const char* password = "passwordWifi";

// const char* htmlContent = "<html><body><h1>Hello, World!</h1></body></html>";

// WiFiServer myServer(80);

// void setup() {
//   Serial.begin(115200);

//   WiFi.begin("nomeWifi", "passwordWifi");
//   while (WiFi.status() != WL_CONNECTED);

//   myServer.begin();
// }

// void loop() {
//   WiFiClient client = myServer.accept();
//   if (!client) return;

//   client.readStringUntil('\r');
//   client.print(htmlContent);
//   client.flush();
//   client.stop();
// };

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "nomeWifi";
const char* password = "passwordWifi";

const char* htmlContent = "<html><body><h1>Hello, World!12222</h1></body></html>";

WiFiServer server(80);



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.accept();
  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);

  client.print(htmlContent);
  client.flush(); // Ensure data is sent

  client.stop();

  // Optional: Delay to avoid overloading the ESP8266
  delay(100);
}
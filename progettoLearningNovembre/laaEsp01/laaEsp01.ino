#include <WiFi.h>

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  WifiSetup();
}

void loop() {
  WifiClient client = server.accept();
  if (!client) return;
  const String request = client.readStringUntil('\r');
  laaClient app(request);

  app.get("ledOn", ledOnLogic);
  app.get("ledOff", ledOffLogic)

  client.stop();
};

class laaClient {
  String _request;
  laaClient(String request) : _request(request) {};
  void get(String directory, void(&callback)()) {
    bool isRequesting = request.indexOf("GET /" + String(directory)) != -1;
    if (!isRequesting) return;
    callback();
  };
}

void ledOnLogic() { digitalWrite(5, HIGH); };
void ledOffLogic() { digitalWrite(5, LOW); };

void WifiSetup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started. Waiting for clients...");
}
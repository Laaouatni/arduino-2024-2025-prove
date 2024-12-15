#include <WiFi.h>

class laaWifiSetup {
  public:
    WiFiServer _server;
    laaWifiSetup() : _server(80) {
      _setup();
    };
  
  private:
    void _setup() {
      Serial.begin(115200);
      WiFi.begin("nomeWifi", "passwordWifi");
      Serial.println("Connecting to WiFi...");
      while (WiFi.status() != WL_CONNECTED) {};
      Serial.println("\nWiFi connected!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      _server.begin();
      Serial.println("Server started. Waiting for clients...");
    };
};

class laaWifiGet {
  private:
    String _request;
    WiFiClient _client;

  public:
    laaWifiGet() {
      WiFiServer _server(80);
      _client = _server.accept();
      if (!_client) return;
      _request = _client.readStringUntil('\r');
    };

    void listenToThisGetRequest(String varName, void(&callback)()) {
      const bool isRequestingThisVarName = _request.indexOf("GET /" + String(varName)) != -1;
      if(!isRequestingThisVarName) return;
      callback();
    };

    void stopListening() {
      _client.println("HTTP/1.1 200 OK");
      _client.println("Content-Type: text/plain");
      _client.println("Access-Control-Allow-Origin: *");
      _client.println();
      _client.println("OK");
      _client.stop();
    };
};

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);

  laaWifiSetup laaWifiSetup;
}

void loop() {
  laaWifiGet get;
  get.listenToThisGetRequest("ledOn", ledOnLogic);
  get.listenToThisGetRequest("ledOff", ledOffLogic);
  get.stopListening();
};

void ledOnLogic() {
  digitalWrite(5, HIGH);
};

void ledOffLogic() {
  digitalWrite(5, LOW);
};
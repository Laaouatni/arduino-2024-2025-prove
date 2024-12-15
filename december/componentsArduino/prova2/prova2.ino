#include <WiFi.h>

WiFiServer server(80);

class laaClient {
  private:
    String _request;

  public:
    laaClient(String requestLineString) : _request(requestLineString) {};
    void get(String filePath, void(&callback)()) {
      bool isRequesting = _request.startsWith("GET /" + String(filePath));
      if (!isRequesting) return;
      callback();
    };
};

void setup() {
  Serial.begin(115200);

  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
  server.begin();

  pinMode(5, OUTPUT);
}

void loop() {
  WiFiClient client = server.accept();
  if (!client) return;
  Serial.println("Client connected! IP Address: " + client.remoteIP().toString());
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");

  laaClient app(client.readStringUntil('\r'));

  app.get("ledOn",  ledOnLogic);
  app.get("ledOff", ledOffLogic);

  client.stop();
};

void ledOnLogic()  { digitalWrite(5, HIGH); };
void ledOffLogic() { digitalWrite(5, LOW); };
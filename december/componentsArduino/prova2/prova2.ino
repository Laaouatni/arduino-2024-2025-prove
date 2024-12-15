#include <WiFi.h>

WiFiServer server(80);

class laaClient {
  private:
    String _request;

  public:
    laaClient(String requestLineString) : _request(requestLineString) {};
    void get(String directory, void(&callback)()) {
      bool isRequesting = _request.indexOf("GET /" + String(directory)) != -1;
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
  // if(!client.available()) return;
  laaClient app = laaClient(client.readStringUntil('\r'));

  // // Rispondi al client
  // client.println("HTTP/1.1 200 OK");
  // client.println("Content-Type: text/plain");
  // client.println("Access-Control-Allow-Origin: *");

  app.get("ledOn",  ledOnLogic);
  app.get("ledOff", ledOffLogic);

  client.stop();
};

void ledOnLogic()  { digitalWrite(5, HIGH); };
void ledOffLogic() { digitalWrite(5, LOW); };
#include <WiFi.h>

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + String(WiFi.localIP()));
  server.begin();

  pinMode(5, OUTPUT);
}

void loop() {
  WiFiClient client = server.accept();
  if (!client) return;
  laaClient app(client.readStringUntil('\r'));

  app.get("ledOn",  ledOnLogic);
  app.get("ledOff", ledOffLogic);

  client.stop();
};

void ledOnLogic()  { digitalWrite(5, HIGH); };
void ledOffLogic() { digitalWrite(5, LOW); };

class laaClient {
  private:
    String _request;

  public:
    laaClient(String requestLineString) : _request(requestLineString) {};
    void get(String directory, void(&callback)()) {
      bool isRequesting = request.indexOf("GET /" + String(directory)) != -1;
      if (!isRequesting) return;
      callback();
    };
};
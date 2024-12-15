#include <WiFi.h>

WiFiServer server(80);

class laaClient {
 private:
  String _request;

 public:
  laaClient(String requestLineString) : _request(requestLineString) {};
  void get(String filePath, void (&callback)()) {
    bool isRequesting = _request.startsWith("GET /" + String(filePath));
    if (!isRequesting) return;
    callback();
  };
  void getDynamic(String filePath, void (&callback)()) {
    const bool isContainingDynamicValueInTheFilePath =
        _request.indexOf(":") != -1;

    if (!isContainingDynamicValueInTheFilePath) {
      bool isRequesting = _request.startsWith("GET /" + String(filePath));
      if (!isRequesting) return;
      callback();
      return;
    }

    struct StringPartsToRemove {
      const String start = "GET ";
      const String end = "HTTP/1.1";
    } stringPartsToRemove;

    struct ModifiedStringWithout {
      String withoutStarting;
      String withoutEnding;
      String withoutStartingAndEnding;
    } modifiedRequestString;

    struct SubstringParams {
      struct End {
        const int from = 0;
        int to =
            (_request.length() - 1) - (stringPartsToRemove.end.length() - 1);
      } end;
      struct Start {
        int from = stringPartsToRemove.start.length() - 1;
      } start;
    } substringParams;

    modifiedRequestString.withoutEnding =
        _request.substring(substringParams.end.from, substringParams.end.to);
    modifiedRequestString.withoutStarting =
        modifiedRequestString.withoutEnding.substring(substringParams.end.from);
  };
};

void setup() {
  Serial.begin(115200);

  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());
  server.begin();

  pinMode(5, OUTPUT);
}

void loop() {
  WiFiClient client = server.accept();
  if (!client) return;
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: keep-alive");

  laaClient app(client.readStringUntil('\r'));

  app.get("ledOn", ledOnLogic);
  app.get("ledOff", ledOffLogic);

  client.stop();
};

void ledOnLogic() { digitalWrite(5, HIGH); };
void ledOffLogic() { digitalWrite(5, LOW); };
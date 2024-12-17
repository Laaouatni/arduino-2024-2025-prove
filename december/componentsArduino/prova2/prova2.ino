// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  server.onNotFound([](AsyncWebServerRequest *request) {
    String urlPath = request->url();
    String valueToReturn;

    auto split = [](String _thisString) { 
      int thisStartIndex = 0;

      int numberOfFoundedParts = 0;

      String foundedSplittedParts[3] = {};

      for (int charIndex = 0; i < _thisString.length(); charIndex++) {
        const char thisChar = _thisString[charIndex];
        
        if(thisChar == "/") {
          foundedSplittedParts[numberOfFoundedParts] =
              _thisString.substring(thisStartIndex, charIndex - 1);
          numberOfFoundedParts++;
          thisStartIndex = charIndex + 1;
        }
      };
    };

    if (urlPath.startsWith("/digitalRead/")){const String pinId = };
    if (urlPath.startWith("/analogRead/")) {
    };
    if (urlPath.startWith("/digitalWrite/")) {
    };
    if (urlPath.startWith("/analogWrite/")) {
    };

    request->send(404, "text/plain", "404")
  });

  server.begin();
}

void loop() {};
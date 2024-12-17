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

  server.onNotFound([](AsyncWebServerRequest* request) {
    String urlPath = request->url();
    String valueToReturn;

    const int MAX_SPLITTED_PARTS = 3;
    int thisStartIndex = 0;
    int numberOfFoundedParts = 0;

    String foundedSplittedParts[MAX_SPLITTED_PARTS];

    for (int charIndex = 0; i < urlPath.length(); charIndex++) {
      const char thisChar = urlPath[charIndex];
      if (numberOfFoundedParts == MAX_SPLITTED_PARTS) break;
      if (thisChar != "/") continue;

      foundedSplittedParts[numberOfFoundedParts] =
          urlPath.substring(thisStartIndex, charIndex - 1);

      numberOfFoundedParts++;
      thisStartIndex = charIndex + 1;
    };

    for (int i = 0; i < 3; i++) {  // Print the 3 parts
      Serial.println(foundedSplittedParts[i]);
    }

    if (urlPath.startsWith("/digitalRead/")) {
      // const String pinId =
    };
    if (urlPath.startsWith("/analogRead/")) {
    };
    if (urlPath.startsWith("/digitalWrite/")) {
    };
    if (urlPath.startsWith("/analogWrite/")) {
    };

    request->send(404, "text/plain", "404");
  });

  server.begin();
}

void loop() {};
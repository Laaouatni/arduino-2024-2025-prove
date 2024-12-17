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
    int thisStartIndex = 0+1;
    int numberOfFoundedParts = 0;

    String foundedSplittedParts[MAX_SPLITTED_PARTS];

    for (int charIndex = thisStartIndex; charIndex < urlPath.length(); charIndex++) {
      const char thisChar = urlPath[charIndex];
      const bool isLastCharIteration = charIndex == urlPath.length()-1;
      const bool isLastAvailablePartInArray = numberOfFoundedParts == MAX_SPLITTED_PARTS;
      const bool isThisCharSlash = thisChar == '/';
      if (isLastAvailablePartInArray || isLastCharIteration) {
        const int choosedEndIndex = isLastCharIteration && isThisCharSlash ? urlPath.length()-1 : urlPath.length();
        foundedSplittedParts[numberOfFoundedParts] = urlPath.substring(thisStartIndex, choosedEndIndex);
        break;
      };
      if (!isThisCharSlash) continue;
      foundedSplittedParts[numberOfFoundedParts] =urlPath.substring(thisStartIndex, charIndex);
      numberOfFoundedParts++;
      thisStartIndex = charIndex+1;
    };

    if (foundedSplittedParts[0] == "digitalRead") {
      const int pinId = foundedSplittedParts[1].toInt();
    };

    if(foundedSplittedParts[0] == "analogRead") {
      const int pinId = foundedSplittedParts[1].toInt();
    };

    if(foundedSplittedParts[0] == "digitalWrite") {
      const int pinId = foundedSplittedParts[1].toInt();
    };

    if (foundedSplittedParts[0] == "analogWrite") {
      const int pinId = foundedSplittedParts[1].toInt();
    };

    request->send(404, "text/plain", "404");
  });

  server.begin();
}

void loop() {};
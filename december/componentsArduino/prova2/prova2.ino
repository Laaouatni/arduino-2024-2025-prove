// c:\Users\laaou\Documents\Arduino\libraries\ESPAsyncWebServer\src\WebAuthentication.cpp
// change mbedtls_md5_starts_ret to mbedtls_md5_starts

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin("nomeWifi", "passwordWifi");
  WiFi.softAP("espWifi", "espPassword");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP local   Address: " + WiFi.localIP().toString());
  Serial.println("WiFi connected! IP hostpot Address: " + WiFi.softAPIP().toString());

  server.onNotFound([](AsyncWebServerRequest* request) {
    String urlPath = request->url();
    String valueToReturn;

    const int MAX_SPLITTED_PARTS = 3;
    int thisStartIndex = 0 + 1;
    int numberOfFoundedParts = 0;

    String foundedSplittedParts[MAX_SPLITTED_PARTS];

    for (int charIndex = thisStartIndex; charIndex < urlPath.length(); charIndex++) {
      const char thisChar = urlPath[charIndex];
      const bool isLastCharIteration = charIndex == urlPath.length() - 1;
      const bool isLastAvailablePartInArray = numberOfFoundedParts == MAX_SPLITTED_PARTS;
      const bool isThisCharSlash = thisChar == '/';
      if (isLastAvailablePartInArray || isLastCharIteration) {
        const int choosedEndIndex = isLastCharIteration && isThisCharSlash ? urlPath.length() - 1 : urlPath.length();
        foundedSplittedParts[numberOfFoundedParts] = urlPath.substring(thisStartIndex, choosedEndIndex);
        break;
      };
      if (!isThisCharSlash) continue;
      foundedSplittedParts[numberOfFoundedParts] = urlPath.substring(thisStartIndex, charIndex);
      numberOfFoundedParts++;
      thisStartIndex = charIndex + 1;
    };

    const String receivedCommandName = foundedSplittedParts[0];
    const int receivedPinId = foundedSplittedParts[1].toInt();
    const int receivedPinValue = foundedSplittedParts[2].toInt();

    if (receivedCommandName == "digitalRead") {
      pinMode(receivedPinId, INPUT);
      request->send(200, "text/plain", String(digitalRead(receivedPinId)));
    };

    if (receivedCommandName == "analogRead") { // 33,32,35,34
      pinMode(receivedPinId, INPUT);
      request->send(200, "text/plain", String(analogRead(receivedPinId)));
    };

    if (receivedCommandName == "digitalWrite") {
      pinMode(receivedPinId, OUTPUT);
      digitalWrite(receivedPinId, receivedPinValue);
      request->send(200, "text/plain", String(digitalRead(receivedPinId)));
    };

    if (receivedCommandName == "analogWrite") {
      pinMode(receivedPinId, OUTPUT);
      analogWrite(receivedPinId, receivedPinValue);
      request->send(200, "text/plain", String(analogRead(receivedPinId)));
    };

    request->send(404, "text/plain", "404");
  });

  server.begin();
}

void loop(){};
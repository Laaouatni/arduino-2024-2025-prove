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
    String urlPath = "HELLO";
    String valueToReturn;

    const int MAX_SPLITTED_PARTS = 5;
    int thisStartIndex = 0+1;
    int numberOfFoundedParts = 0;

    String foundedSplittedParts[MAX_SPLITTED_PARTS] = {};

    Serial.println(foundedSplittedParts[5]);

    // for (int charIndex = thisStartIndex; charIndex < urlPath.length(); charIndex++) {
    //   const char thisChar = urlPath[charIndex];
    //   const bool isLastCharIteration = charIndex == urlPath.length()-1;
    //   const bool isLastAvailablePartInArray = numberOfFoundedParts == MAX_SPLITTED_PARTS;
    //   const bool isThisCharSlash = thisChar == '/';
    //     // Serial.println("BEFOREIF: " + String(numberOfFoundedParts));
    //   if(isLastAvailablePartInArray) {
    //     foundedSplittedParts[numberOfFoundedParts] = urlPath.substring(thisStartIndex);
    //     break;
    //   };
    //   // if(isLastCharIteration) {
    //   //   founded
    //   // }
    //   // if (isLastAvailablePartInArray || isLastCharIteration) {
    //   //   Serial.println("PRIMOIF: " + String(numberOfFoundedParts));
    //   //   const int choosedEndIndex = isLastCharIteration && isThisCharSlash ? urlPath.length()-1 : urlPath.length();
    //   //   foundedSplittedParts[numberOfFoundedParts] = urlPath.substring(thisStartIndex, choosedEndIndex);
    //   //   break;
    //   // };
    //   if (!isThisCharSlash) continue;
    //   // Serial.println("NORMAL: " + String(numberOfFoundedParts) + "\t" + urlPath.substring(thisStartIndex, charIndex));
  

    //   foundedSplittedParts[numberOfFoundedParts] =
    //       urlPath.substring(thisStartIndex, charIndex);
      
    //   numberOfFoundedParts++;
    //   thisStartIndex = charIndex + 1;
    // };

    for (int i = 0; i <= MAX_SPLITTED_PARTS; i++) {  // Print the 3 parts
      Serial.println(String(i) + foundedSplittedParts[i]);
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
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
      int startIndex = 0;
      int endIndex;

      for(auto thisChar : _thisString) {
        if(thisChar)
      }
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
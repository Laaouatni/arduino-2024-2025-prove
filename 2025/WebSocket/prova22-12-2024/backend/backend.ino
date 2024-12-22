#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "passwordWifi");
  while (WiFi.status() != WL_CONNECTED) {
  };
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client,
                AwsEventType type, void *arg, uint8_t *data, size_t len) {
    const bool isConnecting = type == WS_EVT_CONNECT;
    const bool isDisconnecting = type == WS_EVT_DISCONNECT;
    const bool hasData = type == WS_EVT_DATA;

    if (isConnecting)     Serial.println("WebSocket Client Connected! IP Address: " + client->remoteIP().toString());
    if (isDisconnecting)  Serial.println("WebSocket Client Disconnected! IP Address: " + client->remoteIP().toString());
    
    if (!hasData) return;

    ws.textAll("Hello from ESP32 textall" + String((char*)data).substring(0, len));
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    Serial.println("Server Client onNotFound IP Address: " + request->client()->remoteIP().toString());
    request->send(200, "text/plain", "web server call");
  });

  server.addHandler(&ws);
  server.begin();
}

void loop() { 
  ws.cleanupClients(); 
};
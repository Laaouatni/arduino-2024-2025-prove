#include <AsyncTCP.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);
  WiFi.begin("nomeWifi", "12345678");

  if(!LittleFS.begin()) {
    Serial.println("Errore di inizializzazione di 'LittleFS', risolvi e clicca RESET");
    return;
  }
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("WiFi connected! IP Address: " + WiFi.localIP().toString());

  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client,
                AwsEventType type, void *arg, uint8_t *data, size_t len) {
    const bool isConnecting = type == WS_EVT_CONNECT;
    const bool isDisconnecting = type == WS_EVT_DISCONNECT;
    const bool hasData = type == WS_EVT_DATA;

    if (isConnecting)     Serial.println("WebSocket Client Connected! IP Address: " + client->remoteIP().toString());
    if (isDisconnecting)  Serial.println("WebSocket Client Disconnected! IP Address: " + client->remoteIP().toString());
    
    if (!hasData) return;

    const String thisStringData = String((char*)data).substring(0, len);

    ws.textAll(thisStringData);
  });

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  server.addHandler(&ws);
  server.begin();
}

void loop() { 
  ws.cleanupClients(); 
};
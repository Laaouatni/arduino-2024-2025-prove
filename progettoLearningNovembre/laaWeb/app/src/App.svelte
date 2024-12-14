<script lang="ts">
  let isLedOn = $state(true);

  $effect(() => {
    fetch("http://192.168.163.49/led", {
      method: "POST",
      body: JSON.stringify({svelteOn: isLedOn})
    });
    // const url = `http://192.168.163.49/led${isLedOn ? "On" : "Off"}`
    // fetch(url);
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>

<!--
#include <WiFi.h>
#include <ArduinoJson.h>

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);  // LED pin

  wifiSetupBoiderplate();
}

void loop() {
  WiFiClient client = server.accept();
  if (!client) return;
  String request = client.readStringUntil('\r');

  const bool postLedEndpoint  = request.indexOf("POST /led") != -1;

  if(postLedEndpoint) {
    while(client.available()) {
      if(client.readStringUntil('\r') == "\n") break;
    };
    String jsonString = client.readString();
    Serial.println(jsonString);
    JsonDocument doc;
    deserializeJson(doc, jsonString);

    const bool isOn = doc["svelteOn"];
    digitalWrite(5, isOn);
  }

  const bool foundError = false;

  if(!foundError) {
    finishPostRequest(client);
  }

  client.stop();
};

void finishPostRequest(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Access-Control-Allow-Methods: POST, GET, OPTIONS");
  client.println("Access-Control-Allow-Headers: Content-Type");
  client.println();
  client.println("{\"status\":\"success\"}");
}

void wifiSetupBoiderplate() {
  WiFi.begin("nomeWifi", "passwordWifi");
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {};
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started. Waiting for clients...");
}
-->
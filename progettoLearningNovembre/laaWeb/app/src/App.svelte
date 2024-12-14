<script lang="ts">
  let isLedOn = $state(true);

  $effect(() => {
    const url = `http://192.168.163.49/led${isLedOn ? "On" : "Off"}`
    fetch(url);
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>

<!--
#include <WiFi.h>

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

  const bool turnLedOn  = request.indexOf("GET /ledOn") != -1;
  const bool turnLedOff = request.indexOf("GET /ledOff") != -1;

  Serial.println(request + "\t\ton: " + String(turnLedOn) + "\toff: " + String(turnLedOff));

  if (turnLedOn) digitalWrite(5, HIGH);
  else if (turnLedOff) digitalWrite(5, LOW);

  client.stop();
};

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
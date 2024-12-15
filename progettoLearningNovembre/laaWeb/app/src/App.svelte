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
  listenToNewGetRequests("ledOn", ledOnLogic);
  listenToNewGetRequests("ledOff", ledOffLogic);
};

void ledOnLogic() {
  digitalWrite(5, HIGH);
};

void ledOffLogic() {
  digitalWrite(5, LOW);
};

void listenToNewGetRequests(String varName, void(&callback)()) {
  WiFiClient client = server.accept();
  if(!client) return;
  const String request = client.readStringUntil('\r');
  const bool isRequestingThisVarName = request.indexOf("GET /" + String(varName)) != -1;
  if(!isRequestingThisVarName) return;
  Serial.print(request);
  callback();
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
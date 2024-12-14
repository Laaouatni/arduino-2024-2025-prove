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

const char *ssid = "nomeWifi";         // WiFi name
const char *password = "passwordWifi"; // WiFi password

WiFiServer server(80); // Server on port 80

void setup() {
  Serial.begin(115200); // Start Serial Monitor for debugging
  WiFi.begin(ssid, password);
  pinMode(5, OUTPUT); // LED pin

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Indicate connection progress
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print assigned IP address

  server.begin(); // Start server
  Serial.println("Server started. Waiting for clients...");
}

void loop() {
  WiFiClient client = server.accept(); // Check for a new client
  if (!client) return; // If no client, do nothing

  Serial.println("New client connected!"); // Notify new client connection
  
  // Read request line
  String request = client.readStringUntil('\r');
  Serial.print("Request received: ");
  Serial.println(request); // Print the full request for debugging
  
  // Handle /ledOn or /ledOff
  if (request.indexOf("GET /ledOn") != -1) {
    digitalWrite(5, HIGH);
    Serial.println("LED turned ON");
  } else if (request.indexOf("GET /ledOff") != -1) {
    digitalWrite(5, LOW);
    Serial.println("LED turned OFF");
  } else {
    Serial.println("Unknown request"); // For requests not matching /ledOn or /ledOff
  }
  
  client.stop(); // Close connection
  Serial.println("Client disconnected.");
}

-->
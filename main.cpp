#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "TruongHai";
const char *password = "24635722";

const int ledPin = 0; // Pin to which your LED is connected

// HTML code embedded in PROGMEM
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<html>
<head>
  <title>ESP32 LED Control</title>
</head>
<body>
  <h1>ESP32 LED Control</h1>
  <button onclick="ledOn()">Turn On LED</button>
  <button onclick="ledOff()">Turn Off LED</button>

  <script>
    function ledOn() {
      fetch('/led/on');
    }

    function ledOff() {
      fetch('/led/off');
    }
  </script>
</body>
</html>
)rawliteral";

// Create an instance of the server
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Route to control LED
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send(200, "text/plain", "LED turned on");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send(200, "text/plain", "LED turned off");
  });

  // Start server
  server.begin();
}

void loop() {
  // Nothing to do here
}

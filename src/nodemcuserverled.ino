#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "EE";
const char* password = "EEEEEEEE";

ESP8266WebServer server(80);

// Define the pin connected to the LED
const int ledPin = D1; // D1 corresponds to GPIO5 on NodeMCU

void setup() {
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Done");

  // Set up routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP8266 Web Control</title></head><body>";
  html += "<h1>ESP8266 Web Control</h1>";
  html += "<button onclick=\"location.href='/on'\">Turn LED ON</button>";
  html += "<button onclick=\"location.href='/off'\">Turn LED OFF</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/plain", "LED turned ON");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "LED turned OFF");
}

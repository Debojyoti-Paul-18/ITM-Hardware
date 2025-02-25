#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// WiFi credentials
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

// Web server
ESP8266WebServer server(80);

// Pin definitions for second 6 LEDs
const int LED_PINS[6] = {D1, D2, D3, D4, D5, D6}; // Adjust pins as needed

void setup()
{
    Serial.begin(115200);

    // Initialize LED pins
    for (int i = 0; i < 6; i++)
    {
        pinMode(LED_PINS[i], OUTPUT);
        digitalWrite(LED_PINS[i], LOW);
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    // Setup server endpoints
    server.on("/command", HTTP_POST, handleCommand);
    server.begin();
}

void handleCommand()
{
    if (server.hasArg("plain"))
    {
        String message = server.arg("plain");
        DynamicJsonDocument doc(200);
        deserializeJson(doc, message);

        String command = doc["command"].as<String>();
        executeCommand(command);

        server.send(200, "text/plain", "Command received");
    }
}

void executeCommand(String command)
{
    if (command == "phase0")
    {
        digitalWrite(LED_PINS[0], LOW);  // South Green
        digitalWrite(LED_PINS[1], LOW);  // South Yellow
        digitalWrite(LED_PINS[2], HIGH); // South Red
        digitalWrite(LED_PINS[3], LOW);  // East Green
        digitalWrite(LED_PINS[4], LOW);  // East Yellow
        digitalWrite(LED_PINS[5], HIGH); // East Red
    }
    // Add other phases...
}

void loop()
{
    server.handleClient();
}
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

const char *slave_ip = "192.168.31.114";
const int slave_port = 80;

const int LED_PINS[6] = {D1, D2, D3, D4, D5, D6};

bool isTJunction = false;

void setup()
{
    Serial.begin(115200);

    for (int i = 0; i < 6; i++)
    {
        pinMode(LED_PINS[i], OUTPUT);
        digitalWrite(LED_PINS[i], LOW);
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
}

void sendCommandToSlave(const String &command)
{
    HTTPClient http;
    String url = "http://" + String(slave_ip) + ":" + String(slave_port) + "/command";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(200);
    doc["command"] = command;
    String jsonString;
    serializeJson(doc, jsonString);

    int httpCode = http.POST(jsonString);
    http.end();
}

void updateTrafficLights(int phase, bool isTJunction)
{
    switch (phase)
    {
    case 0:
        digitalWrite(LED_PINS[0], HIGH);
        digitalWrite(LED_PINS[1], LOW);
        digitalWrite(LED_PINS[2], LOW);
        digitalWrite(LED_PINS[3], LOW);
        digitalWrite(LED_PINS[4], LOW);
        digitalWrite(LED_PINS[5], HIGH);

        sendCommandToSlave("phase0");
        break;
    }
}

void loop()
{
    for (int phase = 0; phase < 4; phase++)
    {
        updateTrafficLights(phase, isTJunction);

        if (phase % 2 == 0)
        {
            delay(30000);
        }
        else
        {
            delay(3000);
        }
    }
}

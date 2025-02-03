/*
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 921600

lib_deps =
    ESPAsyncWebServer
    DHT sensor library
    Adafruit Unified Sensor
/*

//Prgram starts here  
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define DHTPIN 4       // GPIO where the DHT11 is connected
#define DHTTYPE DHT11  // Define sensor type

const char* ssid = "ICFOSS";     // Replace with your WiFi SSID
const char* password = "n0tava!lableG32!"; // Replace with your WiFi password

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

String getTemperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) return "Error reading temperature!";
    return String(temp) + " °C";
}

String getHumidity() {
    float hum = dht.readHumidity();
    if (isnan(hum)) return "Error reading humidity!";
    return String(hum) + " %";
}

void setup() {
    Serial.begin(921600);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi. IP: " + WiFi.localIP().toString());  //Copy this IP address from serial monitor to get the webpage

    dht.begin();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<html><head><meta http-equiv='refresh' content='2'></head><body>";
        html += "<h1>ESP32 DHT11 Sensor</h1>";
        html += "<p><strong>Temperature:</strong> " + getTemperature() + "</p>";
        html += "<p><strong>Humidity:</strong> " + getHumidity() + "</p>";
        html += "</body></html>";
        request->send(200, "text/html", html);
    });

    server.begin();
}

void loop() {
    // No need to do anything in loop since ESPAsyncWebServer handles requests
}

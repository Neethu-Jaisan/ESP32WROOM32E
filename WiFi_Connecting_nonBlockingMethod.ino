//Write "monitor_speed= 921600" in paltformio.ini

#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID "ICFOSS"
#define WIFI_PASSWORD "n0tava!lableG32!"

int LED= 23;

void setup() {
  Serial.begin(921600);
  pinMode(LED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Starting");

  }

  bool isconnected = false;

  void loop()
  {
    if(WiFi.status()== WL_CONNECTED && !isconnected) {
    Serial.println("Connected");    
    digitalWrite(LED, HIGH);
    isconnected = true;
    }

    else{
    Serial.println(".");    
    digitalWrite(LED, !digitalRead(LED));
    delay(1000);
    isconnected = false;
    }
  }

//if you move away from router and lost connection the loop again executes

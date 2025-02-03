//Write "monitor_speed= 921600" in paltformio.ini

#include <Arduino.h>
#include <WiFiMulti.h>

#define WIFI_SSID "myWIFI" //use ur wifi name
#define WIFI_PASSWORD "Passw0rd" //use ur wifi password
int LED =23;
WiFiMulti wifiMulti;

void setup() {
  Serial.begin(921600);
  pinMode(LED, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while(wifiMulti.run()!= WL_CONNECTED){
    delay(100);
  }

  Serial.println("Connected");
}
  void loop()
  {
    digitalWrite(LED, WiFi.status() == WL_CONNECTED);
  }

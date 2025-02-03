#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Hello from setup");
  }
  void loop()
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Hello from loop");
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Hello from loop");
    delay(1000);
   }

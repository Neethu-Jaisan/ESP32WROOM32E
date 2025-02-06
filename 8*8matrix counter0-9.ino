#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define MAX_DEVICES 1  // Only one 8x8 LED matrix
#define DATA_PIN  23   // MOSI -> DIN
#define CS_PIN    18   // Chip Select -> CS
#define CLK_PIN   5    // Clock -> CLK

MD_Parola display = MD_Parola(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(5); // Set brightness (0-15)
  display.displayClear();
}

void loop() {
  // Display numbers 0 to 9 sequentially
  for (int i = 0; i <= 9; i++) {
    display.setTextAlignment(PA_CENTER);
    display.print(i);  // Show number
    delay(1000);       // Hold for 1 second
    display.displayClear();
  }

  // Scroll "ESP32" continuously
  display.setTextAlignment(PA_CENTER);
  display.displayText("ESP32", PA_CENTER, 100, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  while (!display.displayAnimate()) {
    // Wait until animation completes
  }
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the I2C pins (GPIO21 and GPIO22 are default for ESP32)
#define SDA_PIN 21
#define SCL_PIN 22

// OLED Reset pin (some displays may not need a reset pin, use -1 if not connected)
#define OLED_RESET    -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11 sensor pin
#define DHTPIN 4  // Change this to the GPIO pin you connected the DHT11 data pin to
#define DHTTYPE DHT11  // Specify the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize I2C communication with ESP32 (specifying SDA and SCL pins)
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Use the correct address (0x3C or 0x3D)
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Infinite loop if initialization fails
  }

  Serial.println("OLED Initialized Successfully!");

  // Clear the display buffer
  display.clearDisplay();

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read humidity and temperature from the DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any readings failed and exit early (NaN means failed reading)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text color to white
  display.setTextColor(SSD1306_WHITE);

  // Set text size
  display.setTextSize(1);

  // Set cursor position
  display.setCursor(0, 0);

  // Display temperature and humidity on OLED
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  // Update the display with the buffer content
  display.display();

  // Wait a bit before reading again (e.g., 2 seconds)
  delay(2000);
}

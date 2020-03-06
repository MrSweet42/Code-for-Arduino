#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nStarting...\n");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Hello world");
  display.display();
  delay(1000);
}

void loop() {
  delay(100);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(millis());
  display.display();
}

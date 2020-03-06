#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <time.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
const char* ssid = "smallDIR";
const char* password = "nsmrc2-a+";
int timezone = 3;
unsigned long lastTime = 0;
const unsigned long updateInterval = 1000L;

int getYear() {
  time_t now = time(nullptr);
  struct tm *lt = localtime(&now);
  return 1900 + lt->tm_year;
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println("\n\nStarting...");
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Hello Time");
  display.display();
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Connecting to WiFi");
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(100);
  }
  
  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting time sync");
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Waiting time sync");
  display.display();
  while (!time(nullptr) || getYear() == 1970) {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(200);
  }
  delay(500);
  
  display.setTextSize(2);
  lastTime = millis() - updateInterval;
}

void loop() {

  if (millis() - lastTime > updateInterval) {
    time_t now = time(nullptr);
    Serial.println(ctime(&now));
    struct tm *lt = localtime(&now);
    char str[9];
    strftime(str, sizeof str, "%H:%M:%S", lt);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(str);
    display.display();
    lastTime = millis();
  }
  
}

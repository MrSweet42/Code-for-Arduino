// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

#define WIFI_SERIAL    Serial1

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
  }
  
  Serial.print("Serial setup OK\r\n");
  WIFI_SERIAL.begin(115200);
}

void loop()
{
  if (WIFI_SERIAL.available()) {
    Serial.write(WIFI_SERIAL.read());
  }
  if (Serial.available()) {
    WIFI_SERIAL.write(Serial.read());
  }    
}

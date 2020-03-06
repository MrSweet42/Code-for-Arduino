#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2c Scanner");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf("I2C device found at address %#x\n", address);
      nDevices++;
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found.\n");
  } else {
    Serial.printf("Found %d I2C devices.\n\n", nDevices);
  }
  delay(10000);
}

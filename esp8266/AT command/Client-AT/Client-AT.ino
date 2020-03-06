#define WIFI_SERIAL    Serial1

int timeout = 1000;

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
  }
  Serial.print("Serial setup OK\r\n");
  WIFI_SERIAL.begin(115200);
}

void wifiCommand(String cmd, long timeout) {
  WIFI_SERIAL.println(cmd);
  WIFI_SERIAL.setTimeout(timeout);
  while (!WIFI_SERIAL.available()) {
  }
  while (WIFI_SERIAL.available()) {
    Serial.println(WIFI_SERIAL.readString());
  }
}

void printResponse() {
  while(WIFI_SERIAL.available()) {
    Serial.println(WIFI_SERIAL.readString());
  }
}

void loop()
{
  wifiCommand("AT+CIPMUX=0", timeout);
  wifiCommand("AT+CIPSTART=\"TCP\",\"192.168.2.119\",8080", timeout);
  String params = "?a=a&b=b&t=88";
  String cmd = "GET /" + params + " HTTP/1.1\r\n";
  wifiCommand("AT+CIPSEND=" + String(cmd.length() + 2), timeout);
  wifiCommand(cmd, timeout*4);
  //wifiCommand("AT+CIPCLOSE", timeout);
}

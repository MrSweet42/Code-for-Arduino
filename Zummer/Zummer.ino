// https://www.extramaster.net/tools/midiToArduino/ - .midi превращает в код

int command;
int tonePin = 11;

void setup() {
  Serial.begin (9600);
  pinMode(tonePin, OUTPUT);
}

void sound() {
  delay(56.818125);
  delay(56.818125);
  tone(tonePin, 1567, 51.1363125);
  delay(56.818125);
  delay(56.818125);
  tone(tonePin, 2637, 51.1363125);
  delay(56.818125);
  delay(56.818125);
  tone(tonePin, 2093, 51.1363125);
  delay(56.818125);
  delay(56.818125);
  tone(tonePin, 2349, 51.1363125);
  delay(56.818125);
  delay(56.818125);
  tone(tonePin, 3135, 511.363125);
  delay(568.18125);
}

void loop() {
  command = Serial.read();
  if (command == '1') {
    Serial.println ("Выезжаем!"); 
    sound();
  }
}

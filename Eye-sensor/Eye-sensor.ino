#define SENSOR_LINE_PIN A0
 
void setup() {
  // открываем последовательный порт
  Serial.begin(9600);
}
 
void loop() {
  // считываем значение с датчика
  bool signal = digitalRead(SENSOR_LINE_PIN);
  if ( !signal ) {
    // если сигнал ноль
    // выдаем предупреждение
    Serial.println("Warning! Out of table!");
  } else {
    // если сигнал единица, в нашем случае при истинном значении будет идти сигнал на двигатель
    Serial.println("OK! Above table!");
  }
 
  delay(100);
}

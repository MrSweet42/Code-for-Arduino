#include "IRremote.h"

IRrecv irrecv(8); // указываем вывод, к которому подключен приемник

decode_results results;

void setup() {
  irrecv.enableIRIn(); // запускаем прием
  pinMode(13, OUTPUT);
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    switch ( results.value ) {
    case 0xFFD827: // код кнопки ВКЛ (надо получить при калибровке)
        digitalWrite(13, HIGH);
        break;
    case 0xFF9867: // код кнопки ВЫКЛ (надо получить при калибровке)
        digitalWrite(13, LOW);
        break;
    }    
    irrecv.resume(); // принимаем следующую команду
  }
}

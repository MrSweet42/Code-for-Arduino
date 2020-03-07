#include <MFRC522.h>
#include <Servo.h> 

#define RST_PIN         5          // rst
#define SS_PIN          53         // sda

// Servo myservo; - ДВЕРЬ

// int pos = 0; - ДВЕРЬ

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  // myservo.attach(9); - ДВЕРЬ
}

void loop() {
  byte uidDevice[4] = {0x3B, 0xEB, 0xBA, 0x0C}; // id синенького ключа или id карточки
    
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
  
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
  
    for (byte i  = 0; i < 4; i++) {
      if (uidDevice[i] != mfrc522.uid.uidByte[i]) {
        return;
      }
    }

  Serial.println("OPEN");

  /* ДВЕРЬ
  
  for(pos = 0; pos < 70; pos +=1) {
    myservo.write(pos);
    delay(15);
  }
  delay(2000);
  for(pos = 70; pos >= 0; pos -=1) {
    myservo.write(pos);
    delay(15);
  }
  
  */
  
}  

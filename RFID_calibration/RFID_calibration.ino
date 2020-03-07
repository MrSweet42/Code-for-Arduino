#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53 // sda
#define RST_PIN 5 // rst
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup() {
 Serial.begin(9600); // Initialize serial communications with the PC
 SPI.begin();   // Init SPI bus
 mfrc522.PCD_Init(); // Init MFRC522 card
 Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  byte uidCard[4] = {0x93, 0x48, 0x67, 0x9A}; 
  
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }

 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
 }
          
        for (byte i = 0; i < 4; i++) {
          if (uidCard[i] != mfrc522.uid.uidByte[i])
            return;           
        }
        
  Serial.println("OPEN");
  // digitalWrite(); 
  delay(5000);
  // digitalWrite();      
}

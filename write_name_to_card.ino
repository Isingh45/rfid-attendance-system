/*
 * Utility: Write Name to RFID Card
 *
 * Writes a fixed ASCII name into a MIFARE Classic data block
 * using the default Key A (FF FF FF FF FF FF).
 *
 * Used to initialize cards for the RFID Attendance System.
 * Tested on Arduino Mega + MFRC522.
 */
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 49     // Reset pin
#define SS_PIN 41     // Slave Select pin

MFRC522 mfrc522(SS_PIN, RST_PIN); 

const byte blockNum = 1; // Block to write to (block 1 is safe and usually writable)
byte nameData[] = "Seth"; // Name to write (must be <= 16 bytes for 1 block)
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();      
  mfrc522.PCD_Init();  

  // Default key for MIFARE Classic cards
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("Place your RFID card to write...");
}

void loop() {
  // Look for a card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("Card detected");

  // Authenticate with the card
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(
    MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Prepare a 16-byte buffer (each block is 16 bytes)
  byte buffer[16];
  memset(buffer, 0, sizeof(buffer)); // Clear the buffer
  memcpy(buffer, nameData, min(sizeof(buffer), sizeof(nameData))); // Copy name

  // Write the buffer to the card
  status = mfrc522.MIFARE_Write(blockNum, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Write failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  } else {
    Serial.println("Name written to RFID card!");
  }

  // Halt the card
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(3000);
}

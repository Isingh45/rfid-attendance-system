/*
 * RFID Attendance System - Main Logger
 * 
 * Hardware: Arduino Mega, MFRC522 RFID, 20x4 I2C LCD, SD Card
 * Features:
 *  - UID-based access control
 *  - Reads user name from RFID card memory
 *  - Displays status on LCD
 *  - Logs attendance records to SD card
 *
 * Tested on real hardware.
 */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SdFat.h>

#define RFID_SS 41
#define RFID_RST 49
#define SD_CS 40

MFRC522 mfrc522(RFID_SS, RFID_RST);
LiquidCrystal_I2C lcd(0x27, 20, 4);
SdFat sd;

String valid_user[] = {"D5 A4 26 03", "BB F4 FD 00","2A 8B FD 00","F4 12 2A 03"};

void lcd_display() {
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Please tap card.");
}

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(RFID_SS, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(RFID_SS, HIGH);
  digitalWrite(SD_CS, HIGH);

  lcd.begin(20, 4);
  for (int i = 0; i < 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd_display();

  // Init RFID
  digitalWrite(SD_CS, HIGH);
  digitalWrite(RFID_SS, LOW);
  mfrc522.PCD_Init();
  digitalWrite(RFID_SS, HIGH);

  // Init SD card
  digitalWrite(RFID_SS, HIGH);
  SdSpiConfig sdConfig(SD_CS, DEDICATED_SPI, SD_SCK_MHZ(10));
  if (!sd.begin(sdConfig)) {
    Serial.println("SD Card initialization failed!");
    lcd.clear();
    lcd.print("SD Init Failed!");
  } else {
    Serial.println("SD Card ready.");
    lcd.clear();
    lcd.print("SD Ready.");
    delay(1000);
    lcd_display();

    // Create log.txt with header if it doesn't exist
    if (!sd.exists("log.txt")) {
      File logFile = sd.open("log.txt", FILE_WRITE);
      if (logFile) {
        logFile.println("STATUS        | UID             | NAME        | TIME(ms)");
        logFile.close();
        Serial.println("Created log.txt with header.");
      } else {
        Serial.println("Failed to create log.txt.");
      }
    }
  }
}
void loop() {
  Serial.println("Waiting for card...");

  digitalWrite(SD_CS, HIGH);
  digitalWrite(RFID_SS, LOW);

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(RFID_SS, HIGH);
    return;
  }

  // Format UID
  String uidStr = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uidStr += " ";
  }
  uidStr.toUpperCase();

  Serial.print("UID: ");
  Serial.println(uidStr);

  // Authenticate and read name from block 1
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte blockNum = 1;
  byte buffer[18];  // Slightly bigger than block
  byte size = sizeof(buffer);
  String cardName = "";

  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid)) == MFRC522::STATUS_OK) {
    if (mfrc522.MIFARE_Read(blockNum, buffer, &size) == MFRC522::STATUS_OK) {
      for (int i = 0; i < 16; i++) {
        if (isPrintable(buffer[i])) cardName += (char)buffer[i];
      }
      Serial.print("Card Name: ");
      Serial.println(cardName);
    } else {
      Serial.println("Failed to read name from card.");
      cardName = "Unknown";
    }
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  } else {
    Serial.println("Authentication failed.");
    cardName = "Unknown";
  }

  // Check UID
  bool isValid = false;
  int size_list = sizeof(valid_user) / sizeof(valid_user[0]);
  for (int i = 0; i < size_list; i++) {
    if (uidStr == valid_user[i]) {
      isValid = true;
      break;
    }
  }

  // Display result
  lcd.clear();
  String statusMsg = isValid ? "Access Granted" : "Access Denied";
  lcd.setCursor(0, 0);
  lcd.print(statusMsg);
  lcd.setCursor(0, 1);
  lcd.print("Name: " + cardName);

  Serial.println(statusMsg);

  // Log result to SD card
  digitalWrite(RFID_SS, HIGH);
  digitalWrite(SD_CS, LOW);

  File logFile = sd.open("log.txt", FILE_WRITE);
  if (logFile) {
    logFile.print(statusMsg);
    logFile.print(" | ");
    logFile.print(uidStr);
    logFile.print(" | ");
    logFile.print(cardName);
    logFile.print(" | ");
    logFile.println(millis());
    logFile.close();
    Serial.println("Logged to SD.");
  } else {
    Serial.println("Failed to open log file.");
  }

  digitalWrite(SD_CS, HIGH);
  delay(5000);
  lcd.clear();
  lcd_display();
}

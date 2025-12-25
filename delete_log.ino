/*
 * Utility: Delete Attendance Log
 *
 * Deletes log.txt from the SD card.
 * Used to reset attendance records for the
 * RFID Attendance System.
 */
#include <SPI.h>
#include <SdFat.h>

#define SD_CS 40  // Same as your setup

SdFat sd;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SdSpiConfig sdConfig(SD_CS, DEDICATED_SPI, SD_SCK_MHZ(10));
  if (!sd.begin(sdConfig)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  if (sd.exists("log.txt")) {
    if (sd.remove("log.txt")) {
      Serial.println("log.txt deleted successfully.");
    } else {
      Serial.println("Failed to delete log.txt.");
    }
  } else {
    Serial.println("log.txt does not exist.");
  }
}

void loop() {
  // Nothing to do
}

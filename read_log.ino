/*
 * Utility: Read Attendance Log
 *
 * Reads log.txt from the SD card and prints its contents
 * to the Serial Monitor.
 *
 * Used for maintenance and verification of the
 * RFID Attendance System.
 */
#include <SPI.h>
#include <SdFat.h>

#define SD_CS 40  // Same as in your main project

SdFat sd;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor on some boards

  Serial.println("Initializing SD card...");

  SdSpiConfig sdConfig(SD_CS, DEDICATED_SPI, SD_SCK_MHZ(10));
  if (!sd.begin(sdConfig)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  Serial.println("SD card ready.");

  // Check if log.txt exists
  if (!sd.exists("log.txt")) {
    Serial.println("log.txt not found.");
    return;
  }

  // Open and read log.txt
  File logFile = sd.open("log.txt", FILE_READ);
  if (logFile) {
    Serial.println("----- Contents of log.txt -----");
    while (logFile.available()) {
      Serial.write(logFile.read());
    }
    logFile.close();
    Serial.println("\n----- End of File -----");
  } else {
    Serial.println("Failed to open log.txt");
  }
}

void loop() {
  // Nothing needed here
}

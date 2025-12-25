# rfid-attendance-system
RFID-based attendance system using Arduino, MFRC522, I2C LCD, and SD card logging with SPI bus sharing and maintenance utilities.

# RFID Attendance System

Embedded RFID-based attendance system built on Arduino.

## Features
- MFRC522 RFID reader with card-based user identification
- I2C LCD for real-time user feedback
- SD card logging using SdFat
- Manual SPI chip-select handling to avoid bus conflicts
- Utility sketches to write card names, read logs, and delete logs

## Hardware
- Arduino Mega
- MFRC522 RFID module
- SD card module
- 20x4 I2C LCD

## Notes
This project was designed and tested on real hardware.


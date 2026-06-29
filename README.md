# Embedded RFID Attendance & Access Control System

## Overview

This project implements an embedded RFID-based access control and attendance tracking system using an Arduino Mega 2560. The system authenticates users by reading RFID card UIDs, provides real-time feedback through a 16×2 I2C LCD display, and logs attendance records to a microSD card.

The project demonstrates embedded hardware/software integration by combining RFID communication, SPI and I2C peripherals, modular firmware development, and real-time data logging into a reliable embedded system.

---

## Key Features

* RFID-based user authentication using the MFRC522 RFID reader
* Real-time LCD feedback displaying user information and access status
* Attendance logging to a microSD card with user name and timestamp
* Shared SPI bus management between RFID and SD card peripherals
* Utility programs for RFID card programming, attendance log viewing, and log deletion
* Serial Monitor support for debugging and system validation

---

## System Architecture

The system follows the workflow below:

```text
RFID Card
      ↓
MFRC522 RFID Reader
      ↓
Arduino Mega 2560
      ↓
UID Authentication
      ↓
LCD User Feedback
      ↓
Attendance Logging
      ↓
microSD Card Storage
```

The system integrates multiple communication interfaces while maintaining reliable RFID detection, LCD updates, and SD card logging.

---

## Design Methodology

### Embedded System Development

* Developed firmware using modular Arduino C/C++ programs
* Implemented RFID authentication using unique card identifiers (UIDs)
* Integrated LCD feedback and attendance logging into a unified embedded application
* Organized the project into reusable utility programs for system maintenance and testing

### Hardware Integration

* Integrated the MFRC522 RFID reader, I2C LCD display, and SPI microSD card module
* Managed multiple communication protocols across shared hardware resources
* Implemented voltage-level conversion between the 5V Arduino Mega and the 3.3V RFID module

### Verification & Debugging

* Validated RFID authentication using authorized RFID cards
* Verified attendance logging through CSV records stored on the microSD card
* Used the Arduino Serial Monitor to debug RFID communication, SD card operations, and system behavior

---

## Technologies Used

* Arduino Mega 2560
* Embedded C/C++
* MFRC522 RFID Reader
* SPI Communication
* I2C Communication
* microSD Card Interface
* EEPROM
* Serial Monitor
* Embedded Systems
* Hardware/Software Integration

---

## Repository Structure

```text
images/
    Hardware schematic

source/
    Modular Arduino source code
    • keycard_test.ino
    • read_file.ino
    • del_file.ino
    • set_name.ino

report/
    Final project report

presentation/
    Final project presentation
```

---

## Engineering Challenges

* Managed shared SPI communication between the RFID reader and microSD card module using proper chip-select control
* Resolved voltage compatibility between the 5V Arduino Mega and the 3.3V RFID reader using a resistor-based voltage divider
* Developed modular firmware to simplify testing, debugging, and system maintenance
* Validated reliable attendance logging through iterative hardware and software testing

---

## My Contributions

* Developed and tested embedded firmware for RFID authentication and attendance tracking
* Assisted with hardware integration of the RFID reader, LCD display, and microSD card module
* Contributed to SPI communication management and embedded system debugging
* Implemented and validated attendance logging and utility programs
* Assisted with project testing, documentation, and final presentation

---

## Project Outcome

This project successfully demonstrated an embedded RFID-based attendance and access control system capable of authenticating users, displaying real-time feedback, and maintaining persistent attendance records through microSD storage.

The project strengthened practical experience in embedded systems development, peripheral integration, SPI and I2C communication, firmware debugging, and hardware/software co-design.

---

## Academic Context

**California State University, East Bay**

**Embedded Systems Project**

**Team Members**

* Pierreline Jacob
* Inderpal Singh
* Sanjay

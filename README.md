# RFID Attendance System

An embedded RFID-based attendance tracking system developed using an Arduino Mega 2560, MFRC522 RFID reader, I2C LCD display, and microSD card storage.

## Overview

This project automates attendance tracking by identifying authorized RFID cards, displaying user information on an LCD screen, and logging attendance events to a microSD card.

The system demonstrates embedded-system integration involving RFID communication, SD card storage, LCD interfaces, and shared SPI bus management.

## Features

* RFID-based user identification using MFRC522
* LCD feedback displaying user information and access status
* Attendance logging to microSD card
* Serial Monitor debugging support
* Utility programs for card programming, log viewing, and log deletion
* Shared SPI bus management between RFID and SD card peripherals

## Hardware Used

* Arduino Mega 2560
* MFRC522 RFID Reader
* 16x2 I2C LCD Display
* SPI-Compatible microSD Card Module
* 8GB microSD Card

## Communication Interfaces

### SPI

* MFRC522 RFID Reader
* microSD Card Module

### I2C

* 16x2 LCD Display

### Serial

* Debugging and system validation

## Repository Structure

```text
images/
report/
presentation/
source/
```

## Key Engineering Challenges

* Integrating multiple peripherals across SPI and I2C communication protocols
* Managing chip-select control for RFID and SD card devices sharing the same SPI bus
* Resolving voltage-level compatibility between 5V Arduino logic and 3.3V RFID hardware
* Implementing reliable attendance logging and system validation workflows

## Documentation

* Final Report: `/report`
* Final Presentation: `/presentation`
* Source Code: `/source`

## Skills Demonstrated

* Embedded C/C++
* RFID Integration
* SPI Communication
* I2C Communication
* Serial Debugging
* Hardware-Software Integration
* Real-Time Data Logging
* Embedded System Validation

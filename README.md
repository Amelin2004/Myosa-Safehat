---
publishDate: 2026-05-24T00:00:00Z
title: SAFEHAT PRO — Smart Safety Hat
excerpt: An Arduino-based smart safety helmet that detects falls, confined spaces, and proximity hazards with real-time OLED feedback and emergency SOS signaling.
image: SAFEHAT-PRO/cover.jpg
tags:
  - arduino
  - safety
  - wearable
  - iot
  - embedded
---

> Real-time worker safety monitoring with multi-sensor hazard detection and emergency alerting.

---

## Acknowledgements

This project was developed as an open-source safety innovation. Special thanks to the Arduino community and the contributors who provided sensor libraries, testing feedback, and real-world use-case insights.

---

## Overview

SAFEHAT PRO is an Arduino-based smart safety helmet system designed to enhance worker safety in industrial and confined-space environments. It integrates multiple sensors for real-time hazard detection — including falls, atmospheric pressure anomalies, proximity threats, and emergency signaling — with on-helmet visual feedback via an OLED display.

**What it does:** Continuously monitors a worker's environment and motion to detect falls, confined space entry, nearby hazards, and emergency tap patterns.

**How it works:** An Arduino Nano reads data from an MPU6500 accelerometer/gyroscope, BMP180 barometric pressure sensor, and APDS9930 proximity/ambient light sensor. On-board logic evaluates sensor fusion data to identify safety events and displays alerts on an SH1106 OLED.

**Who it is for:** Construction workers, industrial site personnel, confined-space workers, and lone workers who need an extra layer of safety monitoring.

**What problem it solves:** Delayed emergency response in workplace accidents. The system automatically detects falls, monitors for confined-space entry, and enables manual SOS signaling — reducing response time and potentially saving lives.

---

## Demo / Examples

### Images

<p align="center">
  <img src="/assets/images/SAFEHAT-PRO/circuit.jpg" width="800"><br/>
  <i>Full circuit schematic including power regulation, I²C bus pull-up resistors, and sensor interconnects.</i>
</p>

<p align="center">
  <img src="/assets/images/SAFEHAT-PRO/wiring.jpg" width="800"><br/>
  <i>Wiring connections between the Arduino Nano and all sensor modules.</i>
</p>

<p align="center">
  <img src="/assets/images/SAFEHAT-PRO/components.jpg" width="800"><br/>
  <i>All hardware components used in the SAFEHAT PRO build.</i>
</p>

<p align="center">
  <img src="/assets/images/SAFEHAT-PRO/prototype.jpg" width="800"><br/>
  <i>Assembled prototype mounted on a hard hat shell.</i>
</p>

### Videos

<video controls width="100%">
  <source src="/demo-landscape.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

## Features (Detailed)

### 1. Fall Detection

The MPU6500 accelerometer continuously measures acceleration magnitude. When the magnitude drops below 0.3 G, a freefall state is flagged. If a subsequent impact spike above 2.5 G is detected, the system transitions to an impact state. After impact, if no significant gyroscope movement is detected for 10 seconds, an unconscious worker alert (SOS) is triggered.

### 2. Confined Space Detection

The BMP180 barometric pressure sensor captures baseline atmospheric pressure at startup. A pressure increase exceeding 1500 Pa combined with ambient light dropping below the configured threshold indicates entry into an underground or confined space. The estimated depth is calculated and displayed on the OLED.

### 3. Morse Tap SOS

The accelerometer detects rapid tap gestures. Three taps within 2 seconds are interpreted as a Morse-code SOS trigger (··· --- ···). This allows a conscious but immobile worker to manually signal for help without needing to reach for a radio or phone.

### 4. Proximity Warning

The APDS9930 proximity sensor continuously scans for nearby objects. When an object approaches within the configured threshold, a warning is displayed on the OLED and logged over serial — alerting the worker to potential collision or intrusion hazards.

### 5. OLED Status Display

The SH1106 128×64 OLED provides real-time status messages, sensor readings, and alert notifications directly on the helmet, keeping the worker informed without requiring external displays or devices.

---

## Usage Instructions

1. Power the system using a 5V USB power bank or battery pack connected to the Arduino Nano.
2. On startup, the OLED displays "SAFEHAT PRO" followed by "SYSTEM READY — Monitoring..." once all sensors are initialized.
3. Wear the helmet normally. The system monitors continuously in the background.
4. If a fall occurs, the system automatically detects freefall → impact → potential unconsciousness and triggers an SOS alert on the OLED.
5. To manually trigger an SOS, tap the helmet three times within 2 seconds.
6. The proximity sensor will alert if objects approach too closely.
7. Monitor serial output at 115200 baud for detailed sensor logs and debug information.

---

## Tech Stack

- **Microcontroller:** Arduino Nano (ATmega328P)
- **Motion Sensing:** MPU6500 accelerometer + gyroscope (I²C)
- **Pressure Sensing:** BMP180 barometric pressure / temperature sensor (I²C)
- **Proximity / Light:** APDS9930 digital proximity and ambient light sensor (I²C)
- **Display:** SH1106 128×64 monochrome OLED (I²C)
- **Communication:** I²C (Wire library) for all sensor interconnects
- **Programming Language:** C++ (Arduino Framework)

---

## Requirements / Installation

### Hardware Requirements

| Component | Quantity |
|---|---|
| Arduino Nano (or compatible) | 1 |
| MPU6500 Accelerometer / Gyroscope | 1 |
| BMP180 Barometric Pressure Sensor | 1 |
| APDS9930 Proximity / Ambient Light Sensor | 1 |
| SH1106 128×64 OLED Display | 1 |
| Breadboard | 1 |
| Jumper Wires (M-M, M-F) | 1 set |
| 5V Power Supply (USB or battery pack) | 1 |

### Software Requirements

- Arduino IDE (v1.8.x or v2.x)
- Required libraries (install via Arduino Library Manager):
  - `MPU6500_WE` by Wolfgang Ewald
  - `Adafruit BMP085` by Adafruit
  - `Adafruit SH110X` by Adafruit
  - `Adafruit GFX` by Adafruit

### Installation

1. Clone or download this repository.
2. Open `Myosa.ino` in the Arduino IDE.
3. Install the required libraries via **Tools → Manage Libraries**.
4. Connect the Arduino Nano to your computer via USB.
5. Select the correct board and port under **Tools → Board** and **Tools → Port**.
6. Click **Upload** to flash the firmware.

---

## File Structure

```
Myosa-Safehat/
├── Myosa.ino                  # Main Arduino firmware
├── README.md                  # Project documentation
├── .gitignore                 # Git ignore rules
└── SAFEHAT-PRO/               # Project media assets
    ├── cover.jpg              # Cover image
    ├── circuit.jpg            # Circuit schematic
    ├── wiring.jpg             # Wiring diagram
    ├── components.jpg         # Hardware components
    ├── prototype.jpg          # Assembled prototype
    └── ...                     # Additional images
├── demo-landscape.mp4          # Demo video (landscape)
```

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Contribution Notes

Contributions, issues, and feature requests are welcome. Feel free to open an issue or submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

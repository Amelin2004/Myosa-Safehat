---
publishDate: 2026-05-24T00:00:00Z
title: SAFEHAT PRO — Smart Safety Hat (MYOSA Mini Kit)
excerpt: An ESP32-based smart safety helmet that detects falls, confined spaces, and proximity hazards with real-time OLED feedback and emergency SOS signaling.
image: SAFEHAT-PRO/cover.jpg
tags:
  - arduino
  - esp32
  - myosa
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

SAFEHAT PRO is an ESP32-based smart safety helmet system (MYOSA Mini Kit) designed to enhance worker safety in industrial and confined-space environments. It integrates multiple sensors for real-time hazard detection — including falls, atmospheric pressure anomalies, proximity threats, and emergency signaling — with on-helmet visual feedback via an OLED display.

**What it does:** Continuously monitors a worker's environment and motion to detect falls, confined space entry, nearby hazards, and emergency tap patterns.

**How it works:** An ESP32 reads data from an MPU6050 accelerometer/gyroscope, BMP180 barometric pressure sensor, and APDS9960 proximity/ambient light/gesture sensor. On-board logic evaluates sensor fusion data to identify safety events and displays alerts on an SSD1306 OLED with an audible buzzer alarm.

**Who it is for:** Construction workers, industrial site personnel, confined-space workers, and lone workers who need an extra layer of safety monitoring.

**What problem it solves:** Delayed emergency response in workplace accidents. The system automatically detects falls, monitors for confined-space entry, and enables manual SOS signaling — reducing response time and potentially saving lives.

<video controls width="100%">
  <source src="SAFEHAT-PRO/demo.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

## Demo / Examples

### Images

<p align="center">
  <img src="SAFEHAT-PRO/circuit.jpg" width="800"><br/>
  <i>Full circuit schematic of the ESP32 (MYOSA Mini Kit) including power regulation, I²C bus pull-up resistors, and sensor interconnects.</i>
</p>

<p align="center">
  <img src="SAFEHAT-PRO/fall-detection.jpg" width="800"><br/>
  <i>OLED display showing fall detection alert during freefall and impact events.</i>
</p>

<p align="center">
  <img src="SAFEHAT-PRO/morse-sos.jpg" width="800"><br/>
  <i>Morse tap SOS detection — three taps within 2 seconds trigger an emergency alert.</i>
</p>

<p align="center">
  <img src="SAFEHAT-PRO/hat-on-user.jpg" width="800"><br/>
  <i>SAFEHAT PRO system worn by a user on a hard hat shell.</i>
</p>

<p align="center">
  <img src="SAFEHAT-PRO/hat-prototype.jpg" width="800"><br/>
  <i>Close-up angled view of the assembled SAFEHAT PRO prototype.</i>
</p>

---



## Features (Detailed)

### 1. Fall Detection

The MPU6050 accelerometer continuously measures acceleration magnitude. When the magnitude drops below 0.3 G, a freefall state is flagged. If a subsequent impact spike above 2.5 G is detected, the system transitions to an impact state. After impact, if no significant gyroscope movement is detected for 10 seconds, an unconscious worker alert (SOS) is triggered.

### 2. Confined Space Detection

The BMP180 barometric pressure sensor captures baseline atmospheric pressure at startup. A pressure increase exceeding 1500 Pa combined with ambient light dropping below the configured threshold indicates entry into an underground or confined space. The estimated depth is calculated and displayed on the OLED.

### 3. Morse Tap SOS

The accelerometer detects rapid tap gestures. Three taps within 2 seconds are interpreted as a Morse-code SOS trigger (··· --- ···). This allows a conscious but immobile worker to manually signal for help without needing to reach for a radio or phone.

### 4. Proximity Warning

The APDS9960 proximity sensor continuously scans for nearby objects. When an object approaches within the configured threshold, a warning is displayed on the OLED and logged over serial — alerting the worker to potential collision or intrusion hazards.

### 5. OLED Status Display

The SSD1306 128×64 OLED provides real-time status messages, sensor readings, and alert notifications directly on the helmet, keeping the worker informed without requiring external displays or devices.

---

## Usage Instructions

1. Power the system using a 5V USB power bank or battery pack connected to the ESP32.
2. On startup, the OLED displays "SAFEHAT PRO" followed by "SYSTEM READY — Monitoring..." once all sensors are initialized.
3. Wear the helmet normally. The system monitors continuously in the background.
4. If a fall occurs, the system automatically detects freefall → impact → potential unconsciousness and triggers an SOS alert on the OLED.
5. To manually trigger an SOS, tap the helmet three times within 2 seconds.
6. The proximity sensor will alert if objects approach too closely.
7. Monitor serial output at 115200 baud for detailed sensor logs and debug information.

---

## Tech Stack

- **Microcontroller:** ESP32 (MYOSA Mini Kit)
- **Motion Sensing:** MPU6050 accelerometer + gyroscope (I²C)
- **Pressure Sensing:** BMP180 barometric pressure / temperature sensor (I²C)
- **Proximity / Light:** APDS9960 digital proximity, ambient light, and gesture sensor (I²C)
- **Display:** SSD1306 128×64 monochrome OLED (I²C)
- **Communication:** I²C (Wire library) for all sensor interconnects
- **Programming Language:** C++ (Arduino Framework)

---

## Requirements / Installation

### Hardware Requirements

| Component | Quantity |
|---|---|
| MYOSA Mini Kit (ESP32) | 1 |
| MPU6050 Accelerometer / Gyroscope | 1 |
| BMP180 Barometric Pressure Sensor | 1 |
| APDS9960 Proximity / Ambient Light / Gesture Sensor | 1 |
| SSD1306 128×64 OLED Display | 1 |
| Buzzer | 1 |
| Breadboard | 1 |
| Jumper Wires (M-M, M-F) | 1 set |
| 5V Power Supply (USB or battery pack) | 1 |

### Software Requirements

- Arduino IDE (v1.8.x or v2.x)
- Required libraries (install via Arduino Library Manager):
  - `Adafruit BMP085` by Adafruit
  - `Adafruit APDS9960` by Adafruit
  - `Adafruit SSD1306` by Adafruit
  - `Adafruit GFX` by Adafruit
  - `MPU6050_light` by ejoyneering

### Installation

1. Clone or download this repository.
2. Open `Myosa.ino` in the Arduino IDE.
3. Install ESP32 board support via **Tools → Board → Boards Manager** (search for "ESP32").
4. Install the required libraries via **Tools → Manage Libraries**.
5. Connect the MYOSA Mini Kit (ESP32) to your computer via USB.
6. Select **ESP32 Dev Module** under **Tools → Board → ESP32 Arduino** and the correct port.
7. Click **Upload** to flash the firmware.

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
    ├── fall-detection.jpg     # Fall detection OLED display
    ├── morse-sos.jpg          # Morse tap SOS alert
    ├── hat-on-user.jpg        # Hat worn by user
    ├── hat-prototype.jpg      # Assembled prototype close-up
    └── demo.mp4               # Demo video
```

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Contribution Notes

Contributions, issues, and feature requests are welcome. Feel free to open an issue or submit a pull request. For major changes, please open an issue first to discuss what you would like to change.




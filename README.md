# SAFEHAT PRO — Smart Safety Hat

![SAFEHAT PRO Cover](SAFEHAT-PRO/cover.jpg)

## Overview

SAFEHAT PRO is an Arduino-based smart safety helmet system designed to enhance worker safety in industrial and confined-space environments. It integrates multiple sensors for real-time hazard detection — including falls, atmospheric pressure anomalies, proximity threats, and emergency signaling — with on-helmet visual feedback via an OLED display.

## Features

- **Fall Detection** — MPU6500 accelerometer/gyroscope continuously monitors orientation and impact to detect falls and triggers an alert
- **Confined Space Detection** — BMP180 barometric pressure sensor detects sudden pressure changes indicative of confined or hazardous atmospheric conditions
- **Morse Tap SOS** — Accelerometer-based tap detection interprets Morse-code style taps (··· −−− ···) to activate an emergency SOS sequence
- **Proximity Warning** — APDS9930 ambient light / proximity sensor alerts the wearer when objects or personnel approach too closely
- **OLED Status Display** — SH1106 128×64 OLED shows real-time status, sensor readings, and alert messages

## Hardware Required

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

## Wiring Diagram

<img src="/assets/images/SAFEHAT-PRO/wiring.jpg" alt="Wiring Diagram">

*Wiring connections between the Arduino Nano and all sensor modules.*

## Circuit Schematic

<img src="/assets/images/SAFEHAT-PRO/circuit.jpg" alt="Circuit Schematic">

*Full circuit schematic including power regulation, I²C bus pull-up resistors, and sensor interconnects.*

## Components

<img src="/assets/images/SAFEHAT-PRO/components.jpg" alt="Components">

*All hardware components used in the SAFEHAT PRO build.*

## Prototype

<img src="/assets/images/SAFEHAT-PRO/prototype.jpg" alt="Prototype">

*Assembled prototype mounted on a hard hat shell.*

## Demo Video

<video width="100%" controls>
  <source src="/assets/images/SAFEHAT-PRO/demo-landscape.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

## Acknowledgments

This project was developed as an open-source safety innovation. Special thanks to the Arduino community and the contributors who provided sensor libraries, testing feedback, and real-world use-case insights.

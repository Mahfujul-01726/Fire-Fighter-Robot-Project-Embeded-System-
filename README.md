# 🔥 Autonomous Fire-Fighting Robot (ESP-Distributed System)

![Making Firefighter Robot](Gemini_Generated_Image_673xka673xka673x.png)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-ESP32%20%7C%20ESP8266-blue.svg)](https://www.espressif.com/)

An advanced, multi-microcontroller autonomous system designed for real-time fire detection, navigation, and suppression using a distributed processing architecture.

![Project Architecture](ChatGPT%20Image%20May%2013,%202026,%2011_07_08%20PM.png)

## 📖 Overview
The **Autonomous Firefighter Robot** is a mission-critical embedded system designed to detect and extinguish fires in hazardous environments. Unlike traditional monolithic designs, this project utilizes **three specialized microcontrollers** working in parallel to ensure high reliability, low latency, and modularity.

### The "Brain" Hierarchy
*   **ESP32 (Main Processing Unit):** Manages high-level decisions, sensor fusion, and actuator activation.
*   **ESP8266 (Motion Controller):** Handles low-level motor driving and basic navigation commands.
*   **ESP32-CAM (Vision System):** Provides independent FPV live streaming for remote monitoring.

---

## 🚀 Key Features
- **🔥 Intelligent Fire Detection:** Dual-layer detection using IR Flame sensors for immediate heat source locating.
- **💨 Hazardous Gas Monitoring:** Integrated MQ-2 sensor for detecting Smoke, LPG, CO, and Methane.
- **🛑 Smart Obstacle Avoidance:** Real-time IR proximity sensors prevent collisions in complex environments.
- **💧 Active Suppression System:** Automated high-pressure water pump activated via an isolated relay module.
- **📸 Live Video Telemetry:** Real-time MJPEG streaming over WiFi for remote supervision.
- **⚡ Industrial-Grade Power Design:** Designed for 18650 Li-ion cells with Buck-regulated logic voltage for stability.

---

## 🛠️ Hardware Specification

### Microcontrollers
| Device | Role | Primary Logic |
| :--- | :--- | :--- |
| **ESP32** | Sensor Logic | Fire/Gas detection → Relay activation |
| **ESP8266** | Locomotion | PWM-based speed & direction control |
| **ESP32-CAM** | Telemetry | 2.4GHz WiFi Video Broadcasting |

### Components & Sensors
*   **Actuators:** 4x DC Geared Motors, High-Pressure Water Pump.
*   **Driver:** L298N H-Bridge Motor Driver (supports up to 12V).
*   **Safety:** Isolated 5V/12V Relay Module.
*   **Sensors:** MQ-2 Gas/Smoke Sensor, IR Flame Sensor, IR Proximity Sensor.
*   **Power:** 3x 18650 Battery Pack (7.4V - 11.1V), LM2596 Buck Converter.

---

## 📐 System Workflow

The system operates on a "Sense-Think-Act" loop distributed across devices:

1.  **Sense:** The ESP32 polls the Flame and MQ-2 sensors. Simultaneously, the ESP32-CAM streams video.
2.  **Think:** If the Flame sensor output is **HIGH**, the ESP32 logic enters "Fire Suppression Mode."
3.  **Act:**
    *   **ESP32** triggers the Relay → Pump ON.
    *   **ESP8266** can be commanded to stop or reposition for better coverage.
    *   **ESP32-CAM** transmits the visual confirmation to the operator.

---

## 🔌 Getting Started

### 1. Hardware Assembly
- Follow the **[Full Wiring Guide (PDF)](🛜wire_connection.pdf)** for exact pin mappings.
- **CRITICAL:** Ensure all components share a **Common Ground (GND)**.
- Use a Buck Converter to step down battery voltage to a stable **5V** for the microcontrollers.

### 2. Wiring Overview
- **Motor Control:** ESP8266 (D5-D8) → L298N (IN1-IN4, ENA, ENB).
- **Fire Logic:** ESP32 (GPIO34, 35) → Sensors; ESP32 (GPIO26) → Relay.
- **Vision:** ESP32-CAM connected to a stable 5V source via Buck Converter.

---

## 📺 Media & Demos

| Resource | Description |
| :--- | :--- |
| **[YouTube Playlist](https://www.youtube.com/playlist?list=PLWm-_LfRG8p-kztTce7PdKEiDP4GlUoEz)** | Detailed deep-dive into the entire system. |
| **[Final Demo Video](FireFighter%20Robot_final.mp4)** | The robot in action detecting and extinguishing a fire. |
| **[System Walkthrough](Robot%20Project%20Explanation.mp4)** | Explanation of individual components and wiring. |

---

## 📂 Repository Structure
*   `esp32_fire_detection_system/`: Source code for the ESP32 (Sensor Telemetry via ThingSpeak & Active Water Pump Actuation).
*   `esp8266_smart_car_controller/`: Source code for the ESP8266 Motion Controller (Web-based remote control & motor driving).
*   `SYSTEM_ARCHITECTURE.md`: Detailed pinout and logic tables.
*   `🛜wire_connection.pdf`: High-resolution wiring schematics.
*   `🤖🪫notes.pdf`: Field notes and component specifications.
*   `8266.jpg`: Specific wiring diagram for the ESP8266 motion controller.

---

## 💻 Source Code & Firmware

### 1. ESP32 Fire Detection System (`esp32_fire_detection_system.ino`)
- **Telemetry:** Streams Gas (MQ-2) and Flame sensor data to **ThingSpeak** every 15 seconds.
- **Active Actuation:** Instantly triggers the isolated water pump relay (`GPIO26`) upon detecting hazard thresholds to ensure rapid fire suppression without waiting for API timeouts.

### 2. ESP8266 Smart Car Controller (`esp8266_smart_car_controller.ino`)
- **Remote Control:** Hosts an HTTP web server on port 80 to handle navigation commands (`F`, `B`, `L`, `R`, speed controls, etc.).
- **Hardware Integration Note:** Configured by default for standard motor shields using `D1`-`D4`. If integrating directly with an external **L298N** module as documented in `SYSTEM_ARCHITECTURE.md`, update the pin mappings in the code header (`D3`-`D8`).

---

## 🛠️ Project Gallery & Development

Below are some photos from the development and testing phases, showing the wiring, assembly, and internal components.

| **Wiring Overview** | **Development Bench** |
|:---:|:---:|
| ![Internal Wiring](IMG_20260428_174118.jpg) | ![Testing Phase](IMG20260428170857.jpg) |
| *Labeled connections for ESP8266 and ESP32.* | *Real-time testing with multimeter and documentation.* |

| **Finished Build** | **Component Close-up** |
|:---:|:---:|
| ![Completed Robot](1000099555.jpg) | ![Detailed View](IMG20260428171617.jpg) |
| *The final autonomous firefighter robot.* | *Close-up of the sensor and relay integration.* |

---

## ⚖️ License
Distributed under the **MIT License**. See `LICENSE` for more information.

---
*Created by [Mahfujul](https://github.com/Mahfujul-01726) | May 2026*

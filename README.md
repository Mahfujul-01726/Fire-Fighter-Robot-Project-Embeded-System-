
# 🔥 Autonomous Fire-Fighting Robot

An advanced, multi-microcontroller autonomous system designed for real-time fire detection, navigation, and suppression.

![Project Architecture](ChatGPT%20Image%20May%2013,%202026,%2011_07_08%20PM.png)

## 📖 Overview
This project presents an **Autonomous Firefighter Robot** designed to detect and extinguish fires in hazardous environments with minimal human intervention. The system integrates embedded hardware, sensors, and computer vision to enable real-time fire detection, navigation, and response.

By utilizing a **distributed processing architecture**, the robot offloads specific tasks to specialized microcontrollers, ensuring high reliability and responsive control.

---

## 🚀 Key Features
- **🔥 Autonomous Fire Detection:** Uses specialized flame sensors for 360° or directional fire detection.
- **💨 Gas & Smoke Monitoring:** Integrated MQ-2 sensor for detecting hazardous gases (LPG, Smoke, CO, methane).
- **🛑 Obstacle Avoidance:** IR sensors provide real-time feedback to prevent collisions during navigation.
- **💧 Automatic Suppression:** High-power water pump activated via relay upon fire/gas detection.
- **📸 Live FPV Video:** ESP32-CAM provides a live video stream over WiFi for remote monitoring.
- **🌐 WiFi Enabled:** Remote control and monitoring capabilities via local network.
- **⚡ Robust Power Management:** Designed for 18650 battery packs with stable voltage regulation.

---

## 🛠️ Hardware Components

### Core Microcontrollers
| Controller | Primary Role | Functionality |
|------------|--------------|---------------|
| **ESP32** | Main Processing Unit | Sensor data fusion, decision making, and pump control. |
| **ESP8266** | Movement Control | Motor driver interface and navigation logic. |
| **ESP32-CAM** | Vision System | Independent WiFi video streaming. |

### Sensors & Actuators
*   **Flame Sensor:** Detects infrared light emitted by fire.
*   **MQ-2 Gas Sensor:** Detects smoke and combustible gases.
*   **IR Obstacle Sensor:** Detects objects in the robot's path.
*   **L298N Motor Driver:** Bridges high-power battery to DC motors.
*   **DC Geared Motors (4x):** Provides movement for the chassis.
*   **Relay Module:** Acts as a switch for the water pump.
*   **Water Pump:** High-pressure pump for fire suppression.

---

## 📐 System Architecture

The robot operates through three parallel systems:

1.  **Detection System (ESP32):** Constantly monitors environment sensors. If a flame or high gas concentration is detected, it triggers the relay to activate the water pump.
2.  **Navigation System (ESP8266):** Manages the L298N motor driver to move the robot forward, backward, or turn based on command logic or obstacle data.
3.  **Vision System (ESP32-CAM):** Streams real-time MJPEG video over WiFi, allowing human operators to monitor the situation from a safe distance.

For detailed pinouts and wiring logic, refer to [SYSTEM_ARCHITECTURE.md](SYSTEM_ARCHITECTURE.md).

---

## 🔌 Wiring & Setup

Detailed diagrams and guides are available:
*   **[Infographic Architecture](ChatGPT%20Image%20May%2013,%202026,%2011_07_08%20PM.png)**
*   **[ESP8266 Wiring Diagram](8266.jpg)**
*   **[Full Wiring Guide (PDF)](🛜wire_connection.pdf)**

### ⚠️ Critical Safety Rules
*   **Common Ground:** All microcontrollers and drivers must share a common GND.
*   **Voltage Regulation:** Use a Buck Converter to provide a stable 5V to the ESP32-CAM and ESP32.
*   **Isolation:** Never connect motor pins directly to the ESP boards; always use the L298N driver.

---

## 📺 Media & Demos

Check out the robot in action:
*   **[Detailed System Explanation (YouTube Playlist)](https://www.youtube.com/playlist?list=PLWm-_LfRG8p-kztTce7PdKEiDP4GlUoEz)**
*   **[Project Explanation Video](Robot%20Project%20Explanation.mp4)**
*   **[Final Demonstration](FireFighter%20Robot_final.mp4)**
*   **[Cinematic Showcase](Create_a_futuristic_cinematic.mp4)**

---

## 📂 Project Files
*   `SYSTEM_ARCHITECTURE.md`: Technical specifications and pin mappings.
*   `🛜wire_connection.pdf`: Comprehensive wiring schematics.
*   `🤖🪫notes.pdf`: Additional project notes and technical details.
*   `LICENSE`: MIT License.

---
*Last Updated: May 2026*

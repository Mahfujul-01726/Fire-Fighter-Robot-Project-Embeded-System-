# 🔥 Fire-Fighting Robot - Complete System Architecture

> A fully autonomous fire detection and suppression system using multiple microcontroller boards

---

## 📋 Table of Contents
1. [Power Layout](#-power-layout)
2. [Motor Control (ESP8266)](#-esp8266--motor-control-l298n)
3. [Sensors & Fire System (ESP32)](#-esp32--sensors--relay)
4. [Camera Module (ESP32-CAM)](#-esp32-cam--camera-only)
5. [Full System Overview](#-full-system-integration)
6. [Working Logic](#-working-logic)

---

## ⚡ Power Layout

### System Power Distribution

```
┌─────────────────────────────────┐
│   18650 Battery Pack (7.4-12V)  │
└────────────┬────────────────────┘
             │
      ┌──────┼──────┬──────────┐
      ↓      ↓      ↓          ↓
   L298N   Relay  Buck Conv   Pump
   (Motor) (Pump)  (5V Stable)
                       │
            ┌──────────┼──────────┐
            ↓          ↓          ↓
          ESP8266   ESP32      ESP32-CAM
```

### ⚠️ Critical Rules

| Rule | Status | Description |
|------|--------|-------------|
| **ALL GND Common** | ✅ Required | Connect all ground lines together |
| **ESP32-CAM → 5V Stable** | ✅ Required | Use Buck Converter for stable power |
| **No Direct Motor → ESP** | ❌ Forbidden | DO NOT connect motor lines directly to microcontroller |

---

## 🚗 ESP8266 → Motor Control (L298N)

### Overview
**Microcontroller:** NodeMCU (ESP8266)  
**Function:** Primary motor control and movement commands

### Pin Configuration

| ESP8266 Pin | GPIO | → | L298N Pin | Purpose |
|-------------|------|---|-----------|---------|
| D5 | GPIO14 | → | ENA | Left Motor Enable |
| D6 | GPIO12 | → | ENB | Right Motor Enable |
| D8 | GPIO15 | → | IN1 | Left Motor Forward |
| D7 | GPIO13 | → | IN2 | Left Motor Reverse |
| D4 | GPIO2 | → | IN3 | Right Motor Forward |
| D3 | GPIO0 | → | IN4 | Right Motor Reverse |
| GND | - | → | GND | Common Ground |

### Motor Connections

```
L298N Motor Outputs:
├─ OUT1 + OUT2 → Left Motors
└─ OUT3 + OUT4 → Right Motors
```

### Power Supply

```
Battery (+12V) → L298N +12V
Battery (-GND) → L298N GND
```

### Control Logic Example

```
Direction: FORWARD
├─ Left:  D8=HIGH, D7=LOW  → OUT1,OUT2 Forward
└─ Right: D4=HIGH, D3=LOW  → OUT3,OUT4 Forward

Direction: REVERSE
├─ Left:  D8=LOW, D7=HIGH  → OUT1,OUT2 Reverse
└─ Right: D4=LOW, D3=HIGH  → OUT3,OUT4 Reverse

Direction: LEFT TURN
├─ Left:  D8=LOW, D7=HIGH   → Reverse
└─ Right: D4=HIGH, D3=LOW   → Forward
```

---

## 🔥 ESP32 → Sensors + Relay

### Overview
**Microcontroller:** ESP32  
**Function:** Fire detection, sensor monitoring, and pump activation

---

### 🔥 Flame Sensor

| Flame Sensor | ESP32 | Voltage | Purpose |
|--------------|-------|---------|---------|
| VCC | 3.3V | 3.3V | Power Supply |
| GND | GND | - | Ground Reference |
| DO | GPIO34 | Digital | Fire Detection Output |

**Logic:** `HIGH = Fire Detected`

---

### 💨 MQ-2 Gas Sensor

| MQ-2 Sensor | ESP32 | Voltage | Purpose |
|-------------|-------|---------|---------|
| VCC | 5V | 5V | Power Supply |
| GND | GND | - | Ground Reference |
| DO | GPIO35 | Digital | Gas Detection (Digital) |
| AO | GPIO34* | Analog | Gas Level (Analog, Optional) |

*Requires voltage divider for safe analog reading

**Logic:** `HIGH = Gas Detected`

---

### 🛑 IR Sensor (Obstacle Detection)

| IR Sensor | ESP32 | Voltage | Purpose |
|-----------|-------|---------|---------|
| VCC | 3.3V / 5V | 3.3V-5V | Power Supply |
| GND | GND | - | Ground Reference |
| OUT | GPIO27 | Digital | Obstacle Detection |

**Logic:** `HIGH = Obstacle Detected`

---

### 💧 Relay + Pump

#### Control Side (Low Power)

| Relay Module | ESP32 | Purpose |
|--------------|-------|---------|
| VCC | 5V | Power Supply |
| GND | GND | Ground Reference |
| IN | GPIO26 | Activation Signal |

#### Power Side (High Power)

```
Battery + (12V) → Relay COM (Common)
                 Relay NO (Normally Open) → Pump +
Pump - → Battery GND
```

**Logic:**
- `GPIO26 = HIGH` → Relay Energized → Pump ON
- `GPIO26 = LOW` → Relay De-energized → Pump OFF

---

## 📸 ESP32-CAM → Camera Only

### Pin Configuration

| ESP32-CAM | Connection | Voltage |
|-----------|-----------|---------|
| 5V | Buck Converter Output | 5V Stable |
| GND | Common GND | Ground |

### Key Specifications

✅ **Isolated System** - No connection to ESP32 or ESP8266  
✅ **WiFi Streaming** - Direct WiFi video transmission  
✅ **Independent Operation** - Self-contained video monitoring

---

## 🌐 Full System Integration

### System Architecture Diagram

```
            ┌───────────────────┐
            │   ESP32-CAM       │
            │  (Video WiFi)     │
            ┌─────────┬─────────┐

┌───────────────────┐        ┌──────────────────────┐
│     ESP8266       │        │        ESP32         │
│   Motor Control   │        │ Sensors + Relay      │
┌────────┬──────────┐        ┌───────────┬──────────┐
         │                               │
     L298N Driver                    Sensors
         │                               │
      Motors                        Flame/MQ2/IR
                                         │
                                    Relay → Pump

(All share common GND)
```

### Device Responsibilities

| Device | Role | Primary Function |
|--------|------|------------------|
| **ESP8266** | Movement | Motor control & navigation |
| **ESP32** | Detection & Action | Fire detection & pump activation |
| **ESP32-CAM** | Observation | Real-time video streaming |
| **Battery** | Power | 18650 pack (7.4-12V) |

---

## ⚙️ Working Logic

### 🚗 ESP8266 (Movement System)

```flow
START
  ↓
Listen for Command (WiFi/Bluetooth/Button)
  ↓
[Command Received]
  ├─ FORWARD → GPIO14=HIGH, GPIO12=HIGH
  ├─ REVERSE → GPIO14=LOW, GPIO12=LOW
  ├─ LEFT   → GPIO14=LOW, GPIO12=HIGH
  └─ RIGHT  → GPIO14=HIGH, GPIO12=LOW
  ↓
Apply PWM to ENA/ENB for Speed Control
  ↓
Continue Movement Until Next Command
```

---

### 🔥 ESP32 (Fire Detection System)

```flow
START
  ↓
Initialize Sensors:
  ├─ Flame Sensor (GPIO34)
  ├─ MQ-2 Gas (GPIO35)
  └─ IR Sensor (GPIO27)
  ↓
Continuous Monitoring Loop:
  │
  ├─→ Read Flame Sensor
  │   If HIGH → FIRE DETECTED
  │
  ├─→ Read MQ-2 Sensor
  │   If HIGH → GAS DETECTED
  │
  ├─→ Read IR Sensor
  │   If HIGH → Obstacle Detected
  │
  └─→ Log All Sensor Values
  ↓
[Fire/Gas Detection Logic]
  │
  ├─ IF (Flame OR Gas) DETECTED:
  │    ├─ Set GPIO26 = HIGH
  │    ├─ Activate Relay
  │    ├─ PUMP → ON ✅
  │    ├─ Send Alert
  │    └─ Log Event
  │
  └─ ELSE:
      ├─ Set GPIO26 = LOW
      ├─ Deactivate Relay
      ├─ PUMP → OFF
      └─ Continue Monitoring
  ↓
REPEAT
```

---

### 📸 ESP32-CAM (Video Streaming)

```flow
START
  ↓
Initialize WiFi Connection
  ↓
Start Camera Module
  ↓
Begin WiFi Video Stream:
  ├─ Compress Video Frames
  ├─ Transmit Over WiFi
  └─ Broadcast to Network
  ↓
User accesses video stream:
  ├─ Via Browser (MJPEG Stream)
  ├─ Via Mobile App
  └─ Via Custom Client
  ↓
Continuous Video Feed
  └─ Until Power Off
```

---

## 📊 System Summary

### Specifications at a Glance

```
Power Budget:
├─ Motor Power:    12V @ L298N (High Current)
├─ Control Power:  5V Stable @ Buck Converter
├─ Sensor Power:   3.3V / 5V Mixed
└─ Camera Power:   5V Stable

Microcontrollers:
├─ ESP8266:        Motor Control (4 Motors)
├─ ESP32:          Sensors (3 types) + Relay
└─ ESP32-CAM:      Video Streaming

Sensors:
├─ Flame Detector
├─ Gas Sensor (MQ-2)
└─ Obstacle Sensor (IR)

Actuators:
├─ 4x DC Motors (via L298N)
└─ Water Pump (via Relay)
```

---

## 🔧 Safety Checklist

- [ ] All GND lines properly connected
- [ ] Buck Converter providing stable 5V
- [ ] Motor lines NOT connected directly to GPIO
- [ ] Relay properly isolated with diode protection
- [ ] Battery fully charged before operation
- [ ] All WiFi credentials configured
- [ ] Sensor calibration completed
- [ ] Pump primed with water
- [ ] Emergency stop tested

---

## 📝 Notes

- **Independent Operation:** Systems can operate independently without inter-device communication
- **WiFi-Based Control:** ESP32-CAM streams video; ESP8266/ESP32 receive commands via WiFi/Bluetooth
- **Power Priority:** ESP32-CAM gets stable regulated power; motor control gets direct battery power
- **Safety First:** No direct motor signals to microcontroller pins; always use driver circuit

---

*Last Updated: April 2026*  
*System Type: Autonomous Fire-Fighting Robot*

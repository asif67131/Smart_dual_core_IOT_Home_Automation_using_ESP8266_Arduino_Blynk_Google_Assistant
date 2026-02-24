# 🏠 Dual-Core IoT Hub: Smart Hinge & Security System

A high-performance IoT ecosystem that bridges cloud intelligence with precise hardware execution. This project utilizes an **ESP8266** for multi-platform connectivity (Google Home, Blynk) and an **Arduino Uno** to manage a motorized door assembly featuring a high-torque servo hinge, a synchronized entry light, and an automated solenoid security lock with spring-latch logic.

## 📍 Table of Contents
* [🏠 System Architecture](#system-architecture)
* [🚀 Features](#features)
* [🛠️ Components Used](#components-used)
* [🔌 Circuit Connections](#circuit-connections)
* [⚙️ Installation and Setup](#installation-and-setup)
* [❓ Troubleshooting](#troubleshooting)
* [📂 Source Code](#source-code)
* [🤝 Social Connect](#social-connect)

---

## 🏠 System Architecture <a name="system-architecture"></a>
The system operates on a specialized **Master-Slave Serial Protocol**:

1. **Master (ESP8266):** Acts as the Cloud Gateway. It processes voice packets from **Sinric Pro**, virtual pins from **Blynk**, and sends structured string commands (e.g., `DOOR_OPEN`) to the Arduino via UART.
2. **Slave (Arduino Uno):** Acts as the Hardware Executor. It manages the **PWM signal for the MG996R Servo**, handles the **active-low relay switching** for the 12V Solenoid, and monitors physical button interrupts for the lights.



---

## 🚀 Features <a name="features"></a>
* **Voice-Activated Hinge:** Servo moves 0° to 90° via high-precision PWM control.
* **Spring-Latch Logic:** Solenoid retracts only during the "Open" phase. During "Close," the servo swings the door back, allowing the sloped latch to click shut mechanically, saving power and reducing heat.
* **Cloud-Native:** Fully integrated with Google Assistant and Blynk IoT.
* **Bi-directional Sync:** Manual button presses on the Arduino update the Google Home and Blynk app status in real-time.

---

## 🛠️ Components Used <a name="components-used"></a>
* **Microcontrollers:** 1x NodeMCU ESP8266, 1x Arduino Uno.
* **Motion:** 1x MG996R High-Torque Servo.
* **Security:** 1x 12V DC Solenoid Lock + 1N4007 Diode (Flyback Protection).
* **Switching:** 4-Channel 5V Relay Module.
* **Power:** 12V 2A Adapter (Lock & LED) & 5V 2A Adapter (Servo & Logic).

---

## 🔌 Circuit Connections <a name="circuit-connections"></a>

### 1. The Serial Bridge (UART)
Since the Arduino works at 5V and ESP8266 at 3.3V, a **Voltage Divider** is used on the Arduino's TX line to protect the ESP8266.
* **Arduino TX (Pin 1)** ⮕ `1kΩ Resistor` ⮕ **ESP8266 RX (Pin RX)**
* **ESP8266 RX (Pin RX)** ⮕ `2kΩ Resistor` ⮕ **GND**
* **ESP8266 TX (Pin TX)** ⮕ **Arduino RX (Pin 0)**

### 2. ESP8266 (Master) Pin Mapping
| Component | ESP8266 Pin | Function |
| :--- | :--- | :--- |
| **Status LED** | D7 (GPIO 13) | Heartbeat & Command Indicator |
| **Buzzer** | D8 (GPIO 15) | Audio Feedback for Commands |
| **UART RX/TX** | RX / TX | Communication with Arduino |

### 3. Arduino (Slave) Pin Mapping
| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Servo Signal** | D10 | PWM Control (Required for precise angles) |
| **Relay 1 & 2** | D2, D3 | Light 1 & Light 2 |
| **Relay 3** | D4 | 12V Solenoid Control |
| **Relay 4** | D5 | 12V Synchronized Door Light |
| **Buttons 1 & 2** | D6, D7 | Manual Overrides |
| **Status LED** | A4 | Local Execution Feedback |

---

## ⚙️ Installation and Setup <a name="installation-and-setup"></a>
1. **Libraries:** Install `SinricPro` (by Boris Jaeger), `Blynk`, and `ArduinoOTA`.
2. **Calibration:** Power the Arduino and ensure the Servo is at 0° before attaching the door hinge.
3. **Sync:** Once powered, tell Google Assistant: *"Hey Google, sync my devices."*

---

## ❓ Troubleshooting <a name="troubleshooting"></a>
* **Serial Conflict:** Disconnect the RX/TX wires between the boards while uploading code via USB.
* **Common Ground:** Ensure the GND pins of the 12V supply, 5V supply, Arduino, and ESP8266 are all tied together.
* **Servo Jitter:** Ensure the Servo has its own dedicated 5V 2A power source; do not power it from the Arduino 5V pin.

---

## 📂 Source Code <a name="source-code"></a>
* [📂 ESP8266 Master Code](./ESP8266_Master.ino)
* [📂 Arduino Slave Code](./Arduino_Slave.ino)

---

## 🤝 Social Connect <a name="social-connect"></a>
**Developed by ASIF**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/your-profile-link)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:your-email@example.com)

---

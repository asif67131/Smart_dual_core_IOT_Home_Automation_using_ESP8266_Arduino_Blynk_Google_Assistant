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
3. **Synchronization:** When a physical button is pressed, the Arduino sends a status packet (e.g., `S01`) back to the ESP8266 to update the Google Home and Blynk cloud states.



---

## 🚀 Features <a name="features"></a>
* **Voice-Activated Hinge:** Servo moves 0° to 90° on voice command.
* **Spring-Latch Logic:** Solenoid retracts only during the "Open" phase. During "Close," the servo swings the door back, allowing the sloped latch to click shut mechanically without electrical power.
* **Cloud-Native:** Fully integrated with Google Assistant and Blynk IoT.
* **Dual-Core Reliability:** If WiFi fails, the Arduino continues to manage the door and lights via physical buttons.

---

## 🛠️ Components Used <a name="components-used"></a>
* **Microcontrollers:** 1x NodeMCU ESP8266, 1x Arduino Uno.
* **Motion:** 1x MG996R High-Torque Servo.
* **Security:** 1x 12V DC Solenoid Lock + 1N4007 Diode.
* **Switching:** 4-Channel 5V Relay Module.
* **Power:** 12V 2A Adapter (Lock) & 5V 2A Adapter (Servo/Logic).

---

## 🔌 Circuit Connections <a name="circuit-connections"></a>
### Logic Level Bridge
* **Arduino TX (5V)** ⮕ `1kΩ Resistor` ⮕ **ESP8266 RX (3.3V)**
* **ESP8266 RX** ⮕ `2kΩ Resistor` ⮕ **GND**

### Pin Mapping
| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Servo Signal** | D10 | PWM Control |
| **Relay 1 & 2** | D2, D3 | Light 1 & Light 2 |
| **Relay 3** | D4 | 12V Solenoid |
| **Relay 4** | D5 | Door Light |
| **Buttons** | D6, D7 | Manual Overrides |

---

## ⚙️ Installation and Setup <a name="installation-and-setup"></a>
1. **Libraries:** Install `SinricPro` (by Boris Jaeger), `Blynk`, and `ArduinoOTA`.
2. **Calibration:** Power the Arduino and ensure the Servo is at 0° before attaching the door hinge.
3. **Sync:** Once powered, tell Google Assistant: *"Hey Google, sync my devices."*

---

## ❓ Troubleshooting <a name="troubleshooting"></a>
* **Servo Jitter:** This usually happens due to insufficient current. Ensure the Servo has its own 5V 2A power source and shares a **Common Ground** with the Arduino.
* **Solenoid Overheating:** The code includes a 5-second cutoff for the solenoid. If it stays retracted longer, check the `DOOR_OPEN` delay in the Arduino sketch.
* **Google Home "Offline":** Ensure the ESP8266 Serial Monitor shows `[SinricPro]: Connected`. If not, verify your `APP_KEY` and `APP_SECRET`.

---

## 📂 Source Code <a name="source-code"></a>
* [📂 ESP8266 Master Code](./ESP8266_Master.ino)
* [📂 Arduino Slave Code](./Arduino_Slave.ino)

---

## 🤝 Social Connect <a name="social-connect"></a>
**Developed by ASIF**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/your-profile-link)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:your-email@example.com)

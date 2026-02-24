# 🏠 Dual-Core IoT Hub: Smart Hinge & Security System
An advanced, hybrid home automation system using **ESP8266** for cloud intelligence and **Arduino** for high-torque hardware execution. This project features a motorized door hinge (Servo), an automated security lock (Solenoid), and dual-channel lighting.

---

## 📍 Table of Contents
* [System Architecture](#-system-architecture)
* [Features](#-features)
* [Components Used](#-components-used)
* [Circuit Connections](#-circuit-connections)
* [Installation & Setup](#-installation--setup)
* [Troubleshooting](#-troubleshooting)
* [Source Code](#-source-code)
* [Social Connect](#-social-connect)

---

## ⚙️ System Architecture
This project utilizes a **Master-Slave configuration**:
1. **Master (ESP8266):** Handles WiFi connectivity, Blynk IoT App, Sinric Pro (Google Assistant), and serial command dispatching.
2. **Slave (Arduino):** Executes time-sensitive hardware movements including PWM for the Servo Hinge and Relay switching for the Solenoid/Lights.
3. **Communication:** UART Serial with a Logic Level Divider for bi-directional status synchronization.

---

## 🚀 Features
* **Motorized Door Hinge:** Automatic 90° opening and 0° closing via a high-torque Servo.
* **Smart Security Lock:** 12V Solenoid acts as a spring-latch; unlocks automatically during "Open" command and remains locked during "Close" to allow the door to click shut.
* **Synchronized Entry Lighting:** The door light activates automatically when the door opens and stays ON until the door is closed.
* **Voice Control:** Native Google Assistant integration ("Hey Google, open the door").
* **Live Monitoring:** Real-time status updates on the Blynk IoT app for all channels.
* **Manual Override:** Physical buttons for lighting with instant cloud sync.

---

## 🛠 Components Used
* **Microcontrollers:** 1x NodeMCU (ESP8266), 1x Arduino Uno/Nano.
* **Actuators:** 1x MG996R High-Torque Servo, 1x 12V DC Solenoid Lock, 4-Channel Relay Module.
* **Safety:** 1N4007 Flyback Diode (for Solenoid), 1kΩ & 2kΩ Resistors (Logic Divider).
* **Power:** 12V 2A DC Adapter (for Solenoid), 5V 2A External Supply (for Servo).

---

## 🔌 Circuit Connections
### **Logic Level Bridge**
* **Arduino TX (5V)** ⮕ `1kΩ Resistor` ⮕ **ESP8266 RX (3.3V)**
* **ESP8266 RX** ⮕ `2kΩ Resistor` ⮕ **GND**

### **Pin Mapping**
| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Servo Hinge** | D10 | PWM Signal for Door Movement |
| **Solenoid Lock** | D4 (Relay 3) | 12V Latch Control |
| **Door Light** | D5 (Relay 4) | Synchronized Entry Light |
| **Light 1 & 2** | D2, D3 | Individual Room Lighting |
| **Status LED** | A4 | Visual Command Confirmation |

---

## 📂 Source Code
* [📂 ESP8266 Master Code](./ESP8266_Master.ino) - *Includes Fixed SinricPro v3.0 syntax*
* [📂 Arduino Slave Code](./Arduino_Slave.ino) - *Includes Servo & Spring-Latch Logic*

---

## 🛠 Installation & Setup
1. **Google Home:** Search for **Sinric Pro** in "Works with Google" and link your account.
2. **Servo Calibration:** Ensure the door is physically at 0° when the code starts.
3. **Solenoid Warning:** Always use the 1N4007 diode across the solenoid terminals to prevent ESP8266 resets.

---

## 🤝 Social Connect
**Developed by ASIF**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/your-profile-link)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:your-email@example.com)

---

# 🏠 Dual-Core IoT Hub: 4-Channel Smart Home System
A robust, hybrid home automation system leveraging **ESP8266** for cloud intelligence and **Arduino** for hardware execution. Featuring Google Assistant voice control, Blynk app integration, and physical manual overrides with bi-directional sync.

---

## 📍 Table of Contents
* [System Architecture](#-system-architecture)
* [Features](#-features)
* [Components Used](#-components-used)
* [Circuit Connections](#-circuit-connections)
* [Installation & Setup](#-installation--setup)
* [Troubleshooting](#-troubleshooting)
* [Future Scope](#-future-scope)
* [Source Code](#-source-code)
* [Social Connect](#-social-connect)

---

## ⚙️ System Architecture
This project uses a **Master-Slave configuration**:
1. **Master (ESP8266):** Manages WiFi, Blynk IoT Cloud, Sinric Pro (Google Assistant), and OTA updates.
2. **Slave (Arduino):** Handles 4-channel relay switching, hardware debouncing for buttons, and local LED status feedback.
3. **Communication:** UART Serial with a 5V-to-3.3V Logic Level Divider.

---

## 🚀 Features
* **Voice Control:** Native Google Assistant integration via Sinric Pro.
* **Live Monitoring:** Real-time relay status on Blynk IoT app.
* **Manual Override:** 4 physical buttons that work even if WiFi is disconnected.
* **Bi-directional Sync:** Physical button presses update the Cloud status instantly.
* **OTA Updates:** Flash new firmware to the ESP8266 wirelessly.
* **Visual/Audio Feedback:** 3-second status LED glow and buzzer chirps on commands.

---

## 🛠 Components Used
* **Microcontrollers:** 1x NodeMCU (ESP8266), 1x Arduino Uno/Nano.
* **Actuators:** 1x 4-Channel 5V Relay Module.
* **Inputs:** 4x Tactile Push Buttons.
* **Safety:** 1x 1kΩ Resistor, 1x 2kΩ Resistor (Voltage Divider).
* **Indicators:** 2x LEDs, 1x Active Buzzer.
* **Power:** 5V 2A DC Power Adapter.

---

## 🔌 Circuit Connections
### **Logic Level Bridge**
> ⚠️ **Crucial:** The Arduino TX (5V) must pass through a voltage divider before hitting ESP8266 RX (3.3V).
* **Arduino TX (Pin 1)** ⮕ `1kΩ Resistor` ⮕ **ESP8266 RX**
* **ESP8266 RX** ⮕ `2kΩ Resistor` ⮕ **GND**

---

## 📂 Source Code
* [📂 ESP8266 Master Code](./ESP8266_Master.ino)
* [📂 Arduino Slave Code](./Arduino_Slave.ino)

---

## 🤝 Social Connect
**Developed by ASIF**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/your-profile-link)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:your-email@example.com)

---

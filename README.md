# 🏠 Dual-Core IoT Hub: Smart Home & Precision Irrigation System

**Experience the future of home automation with a high-performance ecosystem that bridges Google Assistant voice intelligence and Blynk IoT mobility with industrial-grade hardware execution.** This project utilizes a dual-core architecture—an **ESP8266** for seamless cloud orchestration and an **Arduino Uno** for precision control over motorized hinges, solenoid security, and intelligent irrigation.

## 🏠 System Architecture
The system operates on a specialized **Master-Slave Serial Protocol** via UART at 9600 Baud:
1. **Master (ESP8266 12E):** Cloud Gateway managing **Blynk IoT**, **Sinric Pro**, and **Google Home Automation** (via **Google Assistant**).
2. **Slave (Arduino Uno):** Hardware Executor managing the **Servo**, **Solenoid**, **Pump**, and **Soil Sensor**.

---

## 🚀 Project Summary
This hub integrates three major cloud ecosystems to provide a seamless user experience:
* **Blynk IoT:** Provides a custom mobile dashboard with a real-time moisture gauge and manual override switches for total control from anywhere.
* **Sinric Pro:** Acts as the bridge for professional smart home device emulation, making your DIY hardware look like official smart appliances.
* **Google Home & Assistant:** Enables hands-free voice commands such as *"Hey Google, open the door"* or *"Turn on the garden lights,"* allowing for full **Google Home Automation** routines and ecosystem-wide accessibility.

---

# IoT-Based Smart Home Monitoring & Control System with Unity3D Digital Twin

This project presents a low-cost, IoT-based **environmental monitoring and control system** designed for smart home applications, enhanced with a fully interactive **Unity3D digital twin house**. The system is built to improve accessibility, especially for low- and middle-income households, offering real-time monitoring, device control, and a 3D visual representation of the home environment.

---

## 🏡 Project Overview

The system uses an **ESP32 microcontroller** interfaced with **digital temperature and humidity sensors** to collect real-time environmental data. This data is transmitted to a **mobile application (Blynk)** as well as an **interactive Unity3D digital twin**, enabling both remote control and visual simulation of household appliances such as fans and lighting systems.

The combination of physical IoT hardware and a virtual Unity-based digital twin provides a modern, intuitive, and immersive Smart Home experience.

---

## 🎯 Key Features

### 🔧 IoT Hardware System
- ESP32 microcontroller for WiFi-enabled control and sensing  
- DHT11/DHT22 temperature & humidity sensors  
- Relay modules for controlling lights, fans, and other appliances  
- Real-time data acquisition and wireless communication  

### 📱 Mobile Application (Blynk)
- Real-time sensor data display  
- Remote switching of appliances  
- Dashboard-based monitoring  
- Low-latency updates and intuitive UI  

### 🏠 Unity3D Digital Twin House
- Custom 3D smart home model built in Unity  
- Real-time synchronization with IoT data  
- Virtual appliances respond to physical device states  
  - Lights turn on/off  
  - Fan rotates according to system state  
- Interactive panels showing live temperature and humidity  
- Supports MQTT, REST API, or Blynk API integration  

---

## 🧰 Technologies Used

### **Hardware**
- ESP32 Development Board  
- DHT11/DHT22 Sensor  
- Relay Module  
- Jumper Wires / Breadboard  

### **Software**
- Arduino IDE (C++ firmware development)  
- Blynk IoT Platform  
- Unity3D (Digital Twin Visualization)  
- MQTT or HTTP for data syncing  

### **Programming Languages**
- C++ (ESP32 firmware)  
- C# (Unity scripts)  
- JSON / REST APIs  

---

## 📐 System Architecture


# 🏥 Smart Health Monitoring System using ESP32  

## 📌 Overview  
The **Smart Health Monitoring System** is an IoT-based project that continuously monitors health parameters like **body temperature** and transmits the data to a cloud-based dashboard (**Node-RED**). The system uses an **ESP32** microcontroller, **DS18B20** temperature sensor, and **Wi-Fi connectivity** to provide real-time health tracking.  

This project is **ideal for elderly patients and remote health monitoring**, allowing caregivers and doctors to monitor health data from anywhere.  

---

## 🛠 Features  
✅ **Temperature Monitoring** – Uses the **DS18B20** sensor for accurate body temperature readings.  
✅ **IoT Connectivity** – Connects to the **Node-RED** IoT platform for remote monitoring.  
✅ **Wi-Fi Enabled** – Data is sent wirelessly to the cloud using ESP32.  
✅ **Local Data Logging** – Uses **SPIFFS (SPI Flash File System)** for data storage on the ESP32.  
✅ **Dashboard Support** – View real-time health data on the **Node-RED dashboard**.  
✅ **Compact & Portable** – Can be integrated into a wearable or bedside device.  

---

## 🖥️ Tech Stack  
🔹 **Microcontroller:** ESP32  
🔹 **Sensors:** DS18B20 (Temperature)  
🔹 **Connectivity:** Wi-Fi, Node-RED  
🔹 **Programming Language:** C++ (Arduino)  
🔹 **Storage:** SPIFFS (ESP32 File System)  

---

## 🏷 Hardware Requirements  
To build this project, you need the following components:  

| Component           | Description                            |  
|--------------------|------------------------------------|  
| ESP32 Dev Board    | The main microcontroller            |  
| DS18B20 Sensor    | Digital temperature sensor         |  
| Resistor (4.7kΩ)   | Pull-up resistor for DS18B20       |  
| Jumper Wires      | For making connections             |  
| Breadboard        | For prototyping connections        |  

---

## 🖥 Software Requirements  
## Before you proceed, ensure you have installed the following:  

✅ **Arduino IDE** – For programming the ESP32
✅ **ESP32 Board Package** – Add ESP32 support in Arduino IDE  
✅ **Node-RED** – Enables cloud communication  
✅ **OneWire & DallasTemperature** – For DS18B20 sensor  
✅ **SPIFFS Library** – For local storage  
---

## 🚀 Installation & Setup  

### 🔹 Step 1: Clone the Repository  
```bash
git clone https://github.com/yourusername/SmartHealthMonitoring.git
cd SmartHealthMonitoring
```
### 🔹 Step 2: Setup Arduino Environment

1️⃣ Install ESP32 board support in Arduino IDE.
2️⃣ Install required libraries (Adafruit MAX30102, OneWire, DallasTemperature).
3️⃣ Open the provided Arduino sketch and modify Wi-Fi credentials.
4️⃣ Upload the code to the ESP32.

### 🔹 Step 3: Setup Node-RED Dashboard

1️⃣ Install Node-RED on your system.
2️⃣ Import the provided Node-RED flow JSON file.
3️⃣ Start Node-RED and access the dashboard via the web interface.



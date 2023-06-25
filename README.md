# Project Title
ESP8266 NodeMCU-based Smart Home System with Web and Android Control using Google Firebase

# Introduction
This project focuses on developing a smart home system using ESP8266 NodeMCU. It enables the control of home devices through a web dashboard and Android interfaces using Google Firebase. The system incorporates various sensors to detect environmental changes and relays for device control. Firebase is utilized for data storage and managing user interactions.

# Features

Date and time display
Relay control for switching devices on/off
Location-based weather information
Fan speed control
Temperature monitoring
Humidity monitoring
Theft alarm
Daylight control using an LDR (Light Dependent Resistor)
Toxic gas alarm

# Sensors and Devices Used

2 x NodeMCU ESP8266
Relay board
DHT11 temperature and humidity sensor
MQ-2 gas sensor
HC-SR501 PIR (Passive Infrared) sensor
LDR (Light Dependent Resistor)
DC motor control driver
9V DC motor

# NodeMCU

The necessary Firebase configurations are implemented on NodeMCU.
Sensor data is sent to Firebase, and Firebase data is processed on NodeMCU.

# Web Dashboard

Firebase connection on the web side is established using JavaScript.
The Firebase data is displayed on the HTML page, and buttons on the page enable control of the Firebase data.

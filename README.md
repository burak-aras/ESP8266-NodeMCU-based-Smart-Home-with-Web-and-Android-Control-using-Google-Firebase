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
```c++
#include <Firebase_ESP_Client.h>

// Insert Firebase project API Key
#define API_KEY "AIzaSyDTSyePp6m8hoQH_3PPuE0-q68k9vYGyYo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://akilliev-faec9-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
void setup() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

```

Sensor data is sent to Firebase, and Firebase data is processed on NodeMCU.  

# Web Dashboard

Firebase connection on the web side is established using JavaScript.  
```javascript
var firebaseConfig = {
  apiKey: "*******************-q68k9vYGyYo",
  authDomain: "akilliev-faec9.firebaseapp.com",
  databaseURL: "https://akilliev-faec9-default-rtdb.firebaseio.com",
  projectId: "akilliev-faec9",
  storageBucket: "akilliev-faec9.appspot.com",
  messagingSenderId: "149016191726",
  appId: "1:149019891726:web:bb8a141383ed09c9ffc9ff",
  measurementId: "G-DP0MG60XXB"
};

// Firebase'i başlat
firebase.initializeApp(firebaseConfig);
'''

The Firebase data is displayed on the HTML page, and buttons on the page enable control of the Firebase data.  

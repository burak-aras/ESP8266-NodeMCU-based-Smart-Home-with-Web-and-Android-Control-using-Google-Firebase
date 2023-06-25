#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
// Motor A connections
int PIRpin = D5;
int enA = D0;
int in1 = D1;
int in2 = D2;
int ldrpin = D7;
int ldrisik = D6;

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Ömer Faruk's Galaxy S20 FE"
#define WIFI_PASSWORD "faruk6607"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDTSyePp6m8hoQH_3PPuE0-q68k9vYGyYo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://akilliev-faec9-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//unsigned long sendDataPrevMillis = 0;
//int count = 0;
bool signupOK = false;

void setup() {
  pinMode(ldrpin, INPUT);
  pinMode(PIRpin, INPUT);
  pinMode(ldrisik, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
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
void fanVerisi() {
  // Firebase üzerindeki röle değerini okur ve belirtilmiş değere göre röleleri açıp kapatır
  if (Firebase.RTDB.getInt(&fbdo, "/FAN")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      int fan = fbdo.to<int>();
      analogWrite(enA, fan * 2);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      Serial.println("Fan");
      Serial.println(fan);
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}
void hareket() {
  if (Firebase.RTDB.getInt(&fbdo, "/PIR/hareketAktif")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      int hareket = fbdo.to<int>();
      Serial.println("hareket");
      Serial.println(hareket);
      if (hareket == 1) {
        int sensorVeri = digitalRead(PIRpin);
        if (sensorVeri == 1) {
          if (Firebase.RTDB.setFloat(&fbdo, "PIR/Hareket", 1)) {
            Serial.print("Hareket Tespti edildi  ");
          } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
        }
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}
void ldrVerisii() {
  if (Firebase.RTDB.getInt(&fbdo, "/Role/ldr")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      int ldr = fbdo.to<int>();
      if (ldr == 1) {
        int ldrVerisi = analogRead(ldrpin);
        Serial.println("----------------------------");
        Serial.println(ldrVerisi);
        Serial.println("ldr verisi");

        if (ldrVerisi != 0) {
          digitalWrite(ldrisik, HIGH);
        } else {
          digitalWrite(ldrisik, LOW);
        }
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}
void loop() {
  if (Firebase.ready() && signupOK) {
    fanVerisi();
    hareket();
    ldrVerisii();
  }
  Serial.println("__________");
}

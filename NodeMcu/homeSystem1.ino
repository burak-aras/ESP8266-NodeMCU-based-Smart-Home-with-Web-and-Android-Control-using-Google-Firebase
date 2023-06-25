#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11
#define RELAY_PIN D1
#define GAZ_PIN D2
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

DHT dht(DHTPIN, DHTTYPE);

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Ömer Faruk's Galaxy S20 FE"
#define WIFI_PASSWORD "faruk6607"

// Insert Firebase project API Key
#define API_KEY "**********************-q68k9vYGyYo"

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
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(DHTPIN, INPUT);
  dht.begin();
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
  roleBaslangic();
}
//Role için firebase üzerinde başlangıç değişkeni atanması
void roleBaslangic() {
  if (Firebase.RTDB.setFloat(&fbdo, "Role/role", 1)) {
    Serial.print("Role: ");
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }  
}
void sicaklikSensor() {
  // Sensör Verisi okunur
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Firebase üzerine sensör verilerini yazdırır
  if (Firebase.RTDB.setFloat(&fbdo, "DHT/humidity", h)) {
    Serial.print("Humidity: ");
    Serial.println(h);
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
  if (Firebase.RTDB.setFloat(&fbdo, "DHT/temperature", t)) {
    //      Serial.println("PASSED");
    Serial.print("Temperature: ");
    Serial.println(t);
  }
}
void roleVerisi() {
  // Firebase üzerindeki röle değerini okur ve belirtilmiş değere göre röleleri açıp kapatır
  if (Firebase.RTDB.getInt(&fbdo, "/Role/role")) {
    if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      int role = fbdo.to<int>();
      Serial.println("Röle Değeri");
      Serial.print(role);
      if (role == 1) {
        digitalWrite(RELAY_PIN, HIGH);
        delay(1000);
      } else {
        digitalWrite(RELAY_PIN, LOW);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}
void gazSensor(){
  int gazDeger = analogRead(D2);
  if (Firebase.RTDB.setFloat(&fbdo, "gaz/gaz", gazDeger)) {
    Serial.print("Gaz Değeri: ");
    Serial.print(gazDeger);
  }
  
}
void loop() {
  if (Firebase.ready() && signupOK) {
    sicaklikSensor();
    roleVerisi();
    gazSensor();
  }
  Serial.println("____");
}

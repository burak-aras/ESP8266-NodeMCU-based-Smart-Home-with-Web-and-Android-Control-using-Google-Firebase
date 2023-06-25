#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servoMotor1;  // Servo nesnesi oluşturuluyor
Servo servoMotor2;
#define trigPin 4
#define echoPin 2
#define trigPin2 11
#define echoPin2 12
#define kirmiziLed 5
#define yesilLed 6
#define buzzerPin 3
#define girisKirmizi 7
#define girisYesil 9
long sure, mesafe;
long sure2, mesafe2;
int aracSayisi = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  servoMotor1.attach(8);
  servoMotor2.attach(10);
  Serial.begin(9600);
  pinMode(kirmiziLed, OUTPUT);
  pinMode(girisKirmizi, OUTPUT);
  pinMode(girisYesil, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(yesilLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd.begin();
}

int mesafeOlcme() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  long mesafe = (sure / 2) * 0.0343;
  return mesafe;
}
int mesafeOlcme2() {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  sure2 = pulseIn(echoPin2, HIGH);
  long mesafe2 = (sure2 / 2) * 0.0343;
  Serial.println(mesafe2);
  return mesafe2;
}
int buzzer = 0;
void bosYer() {

  int bosMesafe = mesafeOlcme2();
  if (bosMesafe <= 10) {
    if (buzzer == 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      buzzer = buzzer + 1;
    }
    digitalWrite(kirmiziLed, HIGH);
    digitalWrite(yesilLed, LOW);
  } else {
    digitalWrite(kirmiziLed, LOW);
    digitalWrite(yesilLed, HIGH);
  }
}
void girisCikis() {
  int i = 1;
  while (i < 5) {
    bosYer();
    int mesafe = mesafeOlcme();
    if (mesafe <= 20) {
      if (mesafe <= 10) {
        if (aracSayisi > 0) {
          aracSayisi = aracSayisi - 1;
          servoMotor1.write(90);
          delay(1000);
          servoMotor1.write(0);
          delay(1000);
        }
        lcd.clear();
        lcd.setCursor(0, 0);  // İlk satırın başlangıç noktası
        lcd.print("cikan araç");
        lcd.setCursor(0, 1);
        lcd.print(aracSayisi);
        while (1) {
          int mesafe1 = mesafeOlcme();
          if (mesafe1 > 10) {
            break;
          } else {
          }
        }
      } else {
        servoMotor2.write(90);
        delay(1000);
        servoMotor2.write(0);
        delay(1000);
        aracSayisi = aracSayisi + 1;
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);  // İlk satırın başlangıç noktası
        lcd.print("giren araç");
        lcd.setCursor(0, 1);
        lcd.print(aracSayisi);
        while (1) {
          int mesafe2 = mesafeOlcme();
          if (mesafe2 < 10 || mesafe2 > 20) {
            break;
          }
        }
      }
      if (aracSayisi < 10) {
        digitalWrite(girisYesil, HIGH);
        digitalWrite(girisKirmizi, LOW);
      } else {
        digitalWrite(girisYesil, LOW);
        digitalWrite(girisKirmizi, HIGH);
      }
    }
  }
}


void loop() {
  girisCikis();
}
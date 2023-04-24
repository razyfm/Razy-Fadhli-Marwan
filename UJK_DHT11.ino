 #define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL69P_OcWrZ"
#define BLYNK_TEMPLATE_NAME "DHT11 Buzzer"
#define BLYNK_AUTH_TOKEN "no4OZW8A2zlPUnRHRBg2ZSs0Z5j_xjBx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Redmi 9";
char pass[] = "zizizizi";

#include "DHT.h"
#define DHTPIN D5      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);
const int Buzzer = D0;

#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);

int setpoint, enable;
bool buzzIndikator;

BlynkTimer timer;

BLYNK_WRITE(V3) {
  setpoint = param.asInt();
}

BLYNK_WRITE(V4) {
  enable = param.asInt();
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();

  pinMode(DHTPIN, INPUT);
  pinMode(Buzzer, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, DHT11data);
}

void DHT11data() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Blynk.virtualWrite(V0, "Hello, ini project Razy!");

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);

  if (t >= setpoint && enable == 1) {
    digitalWrite(Buzzer, 1);
    Blynk.virtualWrite(V5, 1);
    lcd.setCursor(11, 1);
    lcd.print("b:ON ");
  } else {
    digitalWrite(Buzzer, 0);
    Blynk.virtualWrite(V5, 0);
    lcd.setCursor(11, 1);
    lcd.print("b:OFF");
  }

  if (enable == 1) {
    lcd.setCursor(5, 1);
    lcd.print("e:ON ");
  } else {
    lcd.setCursor(5, 1);
    lcd.print("e:OFF");
  }

  lcd.setCursor(0, 0);
  lcd.print("t:");
  lcd.print(t);
  lcd.print("  h:");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("s:");
  lcd.print(setpoint);

  Serial.print(F("T: "));
  Serial.print(t);
  Serial.print(F("°C"));
  Serial.print(F(", H: "));
  Serial.print(h);
  Serial.println(F("%"));
  delay(400);
}

void loop() {
  Blynk.run();
  timer.run();
}

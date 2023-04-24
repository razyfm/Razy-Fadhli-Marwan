#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6EJb7Alfd"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "6gw1c30ydkQ9tcosl7VC7aqlGUEkr9Z4"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Redmi 9";
char pass[] = "zizizizi";

const int SW1 = D1;
const int SW2 = D2;
const int relay1 = D3;
const int relay2 = D4;
const int toggle0 = D5;
const int toggle1 = D6;
const int toggle2 = D7;
int nilaibutton1, nilaibutton2;
int kondisiRelay1, kondisiRelay2;
int state1, state2;

bool bacaTog0, bacaTog1, bacaTog2;

BlynkTimer timer;

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

// kontrol relay 1 dari Blynk
BLYNK_WRITE(V1) {
  kondisiRelay1 = param.asInt();
  digitalWrite(relay1, kondisiRelay1);
}
                        
// kontrol relay 2 dari Blynk
BLYNK_WRITE(V2) {
  kondisiRelay2 = param.asInt();
  digitalWrite(relay2, kondisiRelay2);
}

void smarthome() {
  bacaTog0 = digitalRead(toggle0);
  bacaTog1 = digitalRead(toggle1);
  bacaTog2 = digitalRead(toggle2);

  Blynk.virtualWrite(V0, "Hello, ini adalah project smart home!");

  if (bacaTog0 == 0) {
    Blynk.virtualWrite(V3, "Pintu Utama Tertutup");
    Blynk.virtualWrite(V6, 0);
  } else {
    Blynk.virtualWrite(V3, "Pintu Utama Terbuka");
    Blynk.virtualWrite(V6, 1);
    Blynk.logEvent("pintu_utama", String("telah terbuka!"));
  }

  if (bacaTog1 == 0) {
    Blynk.virtualWrite(V4, "Pintu Belakang Tertutup");
    Blynk.virtualWrite(V7, 0);
  } else {
    Blynk.virtualWrite(V4, "Pintu Belakang Terbuka");
    Blynk.virtualWrite(V7, 1);
    Blynk.logEvent("pintu_belakang", String("telah terbuka!"));
  }

  if (bacaTog2 == 0) {
    Blynk.virtualWrite(V5, "Jendela Samping Tertutup");
    Blynk.virtualWrite(V8, 0);
  } else {
    Blynk.virtualWrite(V5, "Jendela Samping Terbuka");
    Blynk.virtualWrite(V8, 1);
    Blynk.logEvent("jendela_samping", String("telah terbuka!"));
  }

  nilaibutton1 = digitalRead(SW1);  //push button sebagai input relay 1
  if (nilaibutton1 == 0) {
    if (state1 != 0) {
      kondisiRelay1 = !kondisiRelay1;
      digitalWrite(relay1, kondisiRelay1);
      Blynk.virtualWrite(V1, kondisiRelay1);
    }
    state1 = 0;
  } else {
    state1 = 1;
  }

  nilaibutton2 = digitalRead(SW2);  //push button sebagai input relay 2
  if (nilaibutton2 == 0) {
    if (state2 != 0) {
      kondisiRelay2 = !kondisiRelay2;
      digitalWrite(relay2, kondisiRelay2);
      Blynk.virtualWrite(V2, kondisiRelay2);
    }
    state2 = 0;
  } else {
    state2 = 1;
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(20L, smarthome);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(toggle0, INPUT);
  pinMode(toggle1, INPUT);
  pinMode(toggle2, INPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}

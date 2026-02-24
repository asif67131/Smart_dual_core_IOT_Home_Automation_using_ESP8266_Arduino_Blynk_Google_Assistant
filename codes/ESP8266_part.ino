#define BLYNK_TEMPLATE_ID "TMPL3jo7qSjag"
#define BLYNK_TEMPLATE_NAME "Dual core IOT hub"
#define BLYNK_AUTH_TOKEN "gSf14GL2FHozZgQFG-eAEOpjAp-ux9l8"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoOTA.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// WiFi Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ASIF CHAUDHRY";
char pass[] = "11223344";

// Sinric Pro Credentials
#define APP_KEY    "cd226588-e502-4883-980a-6828b452e7c1"
#define APP_SECRET "c21782fc-0f94-4d1b-8bb9-a5975854ce30-a7648f36-b2c5-422c-9a9f-b5bbcfe25f18"
#define ID_LIGHT_1 "699d94e9c2dbd7108b2ef5a5"
#define ID_LIGHT_2 "699d9575db0f6e0b158f4514"
#define ID_DOOR    "699d95b617b32c0941c51d5b"

const int espStatusLed = 13; // D7
const int buzzer = 15;      // D8

// --- FIX: Create global references for the devices ---
SinricProSwitch& mySwitch1 = SinricPro[ID_LIGHT_1];
SinricProSwitch& mySwitch2 = SinricPro[ID_LIGHT_2];
SinricProSwitch& myDoor = SinricPro[ID_DOOR];

bool onPowerState(const String &deviceId, bool &state) {
  if (deviceId == ID_LIGHT_1) {
    Serial.println(state ? "R0_ON" : "R0_OFF");
    Blynk.virtualWrite(V0, state ? 1 : 0);
  } 
  else if (deviceId == ID_LIGHT_2) {
    Serial.println(state ? "R1_ON" : "R1_OFF");
    Blynk.virtualWrite(V1, state ? 1 : 0);
  } 
  else if (deviceId == ID_DOOR) {
    if (state) {
      Serial.println("DOOR_OPEN");
      Blynk.virtualWrite(V2, 1);
    } else {
      Serial.println("DOOR_CLOSE");
      Blynk.virtualWrite(V2, 0);
    }
  }
  digitalWrite(espStatusLed, HIGH);
  digitalWrite(buzzer, HIGH); delay(100); digitalWrite(buzzer, LOW);
  delay(2000); digitalWrite(espStatusLed, LOW);
  return true;
}

void setup() {
  Serial.begin(9600);
  pinMode(espStatusLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  Blynk.begin(auth, ssid, pass);
  ArduinoOTA.begin();

  // Register callbacks using the global references
  mySwitch1.onPowerState(onPowerState);
  mySwitch2.onPowerState(onPowerState);
  myDoor.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  Blynk.run();
  SinricPro.handle();
  ArduinoOTA.handle();

  if (Serial.available() > 0) {
    String feedback = Serial.readStringUntil('\n');
    feedback.trim();
    if (feedback.startsWith("S")) {
      int id = feedback.substring(1, 2).toInt();
      int state = feedback.substring(2).toInt();
      Blynk.virtualWrite(id, state);
      
      // --- FIX: Use the switch references to send events ---
      if(id == 0) mySwitch1.sendPowerStateEvent(state == 1);
      if(id == 1) mySwitch2.sendPowerStateEvent(state == 1);
    }
  }
}
#define BLYNK_TEMPLATE_ID "abc"
#define BLYNK_TEMPLATE_NAME "Dual core IOT hub"
#define BLYNK_AUTH_TOKEN "abc"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SinricPro.h>
#include <SinricProLight.h> 

// Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "abc";
char pass[] = "abc";

#define APP_KEY    "xyz"
#define APP_SECRET "xyz"
#define ID_LIGHT_1 "xyz"
#define ID_LIGHT_2 "xyz"
#define ID_DOOR    "xyz"

const int onboardLED = 2; 

// LED Animation Variables
int brightness = 0;
int fadeAmount = 5;
unsigned long lastLEDUpdate = 0;

// Tracking local state
bool stateL1 = false;
bool stateL2 = false;
bool stateDoor = false;

// --- Sinric Pro Callbacks ---
bool onPowerState_L1(const String &deviceId, bool &state) {
  stateL1 = state;
  Serial.println(state ? "L1_ON" : "L1_OFF");
  Blynk.virtualWrite(V1, state);
  return true;
}

bool onPowerState_L2(const String &deviceId, bool &state) {
  stateL2 = state;
  Serial.println(state ? "L2_ON" : "L2_OFF");
  Blynk.virtualWrite(V2, state);
  return true;
}

bool onPowerState_Door(const String &deviceId, bool &state) {
  stateDoor = state;
  Serial.println(state ? "DR_OPEN" : "DR_CLOSE");
  Blynk.virtualWrite(V3, state);
  return true;
}

// --- Blynk Callbacks ---
BLYNK_WRITE(V1) {
  stateL1 = param.asInt();
  Serial.println(stateL1 ? "L1_ON" : "L1_OFF");
  SinricProLight &myLight = SinricPro[ID_LIGHT_1];
  myLight.sendPowerStateEvent(stateL1);
}

BLYNK_WRITE(V2) {
  stateL2 = param.asInt();
  Serial.println(stateL2 ? "L2_ON" : "L2_OFF");
  SinricProLight &myLight = SinricPro[ID_LIGHT_2];
  myLight.sendPowerStateEvent(stateL2);
}

BLYNK_WRITE(V3) {
  stateDoor = param.asInt();
  Serial.println(stateDoor ? "DR_OPEN" : "DR_CLOSE");
  SinricProLight &myDoor = SinricPro[ID_DOOR];
  myDoor.sendPowerStateEvent(stateDoor);
}

BLYNK_WRITE(V4) { 
  int val = param.asInt();
  Serial.println(val ? "PUMP_ON" : "PUMP_OFF");
}

void setup() {
  Serial.begin(9600); 
  pinMode(onboardLED, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);

  // Setup SinricPro devices
  SinricProLight &light1 = SinricPro[ID_LIGHT_1];
  light1.onPowerState(onPowerState_L1);

  SinricProLight &light2 = SinricPro[ID_LIGHT_2];
  light2.onPowerState(onPowerState_L2);

  SinricProLight &door = SinricPro[ID_DOOR];
  door.onPowerState(onPowerState_Door);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  Blynk.run();
  SinricPro.handle(); // Modern call for v4.1.x
  handleLEDStatus();
  handleIncomingSerial();
}

void handleLEDStatus() {
  unsigned long currentMillis = millis();
  if (WiFi.status() != WL_CONNECTED) {
    if (currentMillis - lastLEDUpdate >= 200) {
      digitalWrite(onboardLED, !digitalRead(onboardLED));
      lastLEDUpdate = currentMillis;
    }
    return;
  }
  if (currentMillis - lastLEDUpdate >= 30) {
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) fadeAmount = -fadeAmount;
    analogWrite(onboardLED, 255 - brightness); 
    lastLEDUpdate = currentMillis;
  }
}

void handleIncomingSerial() {
  if (Serial.available() > 0) {
    String incoming = Serial.readStringUntil('\n');
    incoming.trim();

    if (incoming == "BTN1_PRESS") {
      stateL1 = !stateL1;
      Blynk.virtualWrite(V1, stateL1);
      SinricProLight &myLight = SinricPro[ID_LIGHT_1];
      myLight.sendPowerStateEvent(stateL1);
    }
    else if (incoming == "BTN2_PRESS") {
      stateL2 = !stateL2;
      Blynk.virtualWrite(V2, stateL2);
      SinricProLight &myLight = SinricPro[ID_LIGHT_2];
      myLight.sendPowerStateEvent(stateL2);
    }
    else if (incoming == "BTN_DOOR_PRESS") {
      stateDoor = !stateDoor;
      Blynk.virtualWrite(V3, stateDoor);
      SinricProLight &myDoor = SinricPro[ID_DOOR];
      myDoor.sendPowerStateEvent(stateDoor);
    }
    else if (incoming.startsWith("SOIL:")) {
      int soilVal = incoming.substring(5).toInt();
      Blynk.virtualWrite(V5, soilVal);
    }
  }
}

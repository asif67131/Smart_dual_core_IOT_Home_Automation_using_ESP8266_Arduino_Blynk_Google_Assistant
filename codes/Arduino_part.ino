#include <Servo.h>

// --- Pin Definitions ---
const int RELAY_L1 = 2;
const int RELAY_L2 = 3;
const int RELAY_SOLENOID = 4;
const int RELAY_PUMP = 5;

const int BTN_L1 = 7;
const int BTN_L2 = 8;
const int BTN_SOLENOID = 12;

const int SOIL_SENSOR_SIG = A0; 
const int SOIL_SENSOR_PWR = 13; // Power pin to prevent corrosion

const int SERVO_PIN = 9;
const int DOOR_LED = 6;       
const int INDICATOR_LED = 11; 

// --- Objects & Variables ---
Servo doorServo;
unsigned long lastSoilCheck = 0;
unsigned long doorOpenMillis = 0;
bool doorIsOpening = false;
bool doorPhysicalState = false; 

int brightness = 0;
int fadeAmount = 5;
unsigned long lastLEDUpdate = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(RELAY_L1, OUTPUT);
  pinMode(RELAY_L2, OUTPUT);
  pinMode(RELAY_SOLENOID, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  
  // Initialize Relays OFF (Active Low)
  digitalWrite(RELAY_L1, HIGH);
  digitalWrite(RELAY_L2, HIGH);
  digitalWrite(RELAY_SOLENOID, HIGH);
  digitalWrite(RELAY_PUMP, HIGH);

  pinMode(BTN_L1, INPUT_PULLUP);
  pinMode(BTN_L2, INPUT_PULLUP);
  pinMode(BTN_SOLENOID, INPUT_PULLUP);
  pinMode(DOOR_LED, OUTPUT);
  pinMode(INDICATOR_LED, OUTPUT);
  
  pinMode(SOIL_SENSOR_PWR, OUTPUT);
  digitalWrite(SOIL_SENSOR_PWR, LOW); 
  
  doorServo.attach(SERVO_PIN);
  doorServo.write(0); 
}

void loop() {
  handleSerialInput();
  handlePhysicalButtons();
  handleSoilAutomation();
  handleIndicatorLED();
  handleDoorTimer();
}

void handleSerialInput() {
  if (Serial.available() > 0) {
    flickerIndicator();
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "L1_ON")  digitalWrite(RELAY_L1, LOW);
    if (cmd == "L1_OFF") digitalWrite(RELAY_L1, HIGH);
    if (cmd == "L2_ON")  digitalWrite(RELAY_L2, LOW);
    if (cmd == "L2_OFF") digitalWrite(RELAY_L2, HIGH);
    
    if (cmd == "DR_OPEN")  openDoorSequence();
    if (cmd == "DR_CLOSE") closeDoorSequence();
    
    if (cmd == "PUMP_ON")  digitalWrite(RELAY_PUMP, LOW);
    if (cmd == "PUMP_OFF") digitalWrite(RELAY_PUMP, HIGH);
  }
}

void handlePhysicalButtons() {
  if (digitalRead(BTN_L1) == LOW) {
    digitalWrite(RELAY_L1, !digitalRead(RELAY_L1));
    Serial.println("BTN1_PRESS"); 
    flickerIndicator();
    delay(400); 
  }
  
  if (digitalRead(BTN_L2) == LOW) {
    digitalWrite(RELAY_L2, !digitalRead(RELAY_L2));
    Serial.println("BTN2_PRESS");
    flickerIndicator();
    delay(400);
  }
  
  if (digitalRead(BTN_SOLENOID) == LOW) {
    if(!doorPhysicalState) openDoorSequence();
    else closeDoorSequence();
    
    Serial.println("BTN_DOOR_PRESS");
    flickerIndicator();
    delay(400);
  }
}

void handleSoilAutomation() {
  // Interval set to 10 seconds (10000ms)
  if (millis() - lastSoilCheck > 10000) {
    
    // Power on sensor, wait for stabilization, then read
    digitalWrite(SOIL_SENSOR_PWR, HIGH);
    delay(20); 
    int rawValue = analogRead(SOIL_SENSOR_SIG);
    digitalWrite(SOIL_SENSOR_PWR, LOW); // Turn off immediately
    
    // Map values: 1023 (Dry) to 200 (Very Wet)
    int moisturePercent = map(rawValue, 1023, 200, 0, 100);
    moisturePercent = constrain(moisturePercent, 0, 100);
    
    // Send to ESP8266 for Blynk Gauge
    Serial.print("SOIL:");
    Serial.println(moisturePercent);

    // Trigger pump if below 20%
    if (moisturePercent < 20) {
      digitalWrite(RELAY_PUMP, LOW);
      delay(1000); 
      digitalWrite(RELAY_PUMP, HIGH);
    }
    lastSoilCheck = millis();
  }
}

void openDoorSequence() {
  digitalWrite(RELAY_SOLENOID, LOW); 
  doorServo.write(90);
  digitalWrite(DOOR_LED, HIGH);
  doorOpenMillis = millis();
  doorIsOpening = true;
  doorPhysicalState = true;
}

void closeDoorSequence() {
  doorServo.write(0);
  digitalWrite(DOOR_LED, LOW);
  digitalWrite(RELAY_SOLENOID, HIGH); 
  doorIsOpening = false;
  doorPhysicalState = false;
}

void handleDoorTimer() {
  if (doorIsOpening && (millis() - doorOpenMillis > 3000)) {
    digitalWrite(RELAY_SOLENOID, HIGH); 
    doorIsOpening = false;
  }
}

void handleIndicatorLED() {
  if (millis() - lastLEDUpdate >= 30) {
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) fadeAmount = -fadeAmount;
    analogWrite(INDICATOR_LED, brightness);
    lastLEDUpdate = millis();
  }
}

void flickerIndicator() {
  for(int i=0; i<4; i++) {
    digitalWrite(INDICATOR_LED, HIGH); delay(40);
    digitalWrite(INDICATOR_LED, LOW);  delay(40);
  }
}

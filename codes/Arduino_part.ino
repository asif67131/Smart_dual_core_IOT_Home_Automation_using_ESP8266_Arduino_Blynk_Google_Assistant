#include <Servo.h>

Servo doorHinge;

// Pin Definitions
const int relayPins[] = {2, 3, 4, 5}; // 0:Light1, 1:Light2, 2:Solenoid, 3:DoorLight
const int buttonPins[] = {6, 7};      // Physical buttons for Light 1 and 2
const int servoPin = 10;
const int statusLed = A4;

bool relayStates[] = {HIGH, HIGH, HIGH, HIGH}; // Active LOW relays
bool lastButtonStates[] = {HIGH, HIGH};

void setup() {
  Serial.begin(9600);
  doorHinge.attach(servoPin);
  pinMode(statusLed, OUTPUT);
  
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); 
  }
  
  for (int i = 0; i < 2; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  doorHinge.write(0); // Ensure door starts closed
}

void loop() {
  // 1. Handle Serial Commands from ESP8266
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "R0_ON") digitalWrite(relayPins[0], LOW);
    else if (command == "R0_OFF") digitalWrite(relayPins[0], HIGH);
    else if (command == "R1_ON") digitalWrite(relayPins[1], LOW);
    else if (command == "R1_OFF") digitalWrite(relayPins[1], HIGH);
    
    else if (command == "DOOR_OPEN") {
      digitalWrite(relayPins[3], LOW);    // Door Light ON
      digitalWrite(relayPins[2], LOW);    // Unlock Solenoid
      delay(800);                         // Wait for latch to pull back
      doorHinge.write(90);                // Swing door open
      delay(4200);                        // Keep solenoid open for 5s total
      digitalWrite(relayPins[2], HIGH);   // Lock Solenoid (Spring-latch ready)
      digitalWrite(statusLed, HIGH); delay(1000); digitalWrite(statusLed, LOW);
    }
    else if (command == "DOOR_CLOSE") {
      doorHinge.write(0);                 // Swing door closed
      digitalWrite(relayPins[3], HIGH);   // Door Light OFF
      // Note: Solenoid Relay (2) is NOT touched. Door latches mechanically.
      digitalWrite(statusLed, HIGH); delay(1000); digitalWrite(statusLed, LOW);
    }
  }

  // 2. Handle Physical Buttons (Toggle logic)
  for (int i = 0; i < 2; i++) {
    bool currentState = digitalRead(buttonPins[i]);
    if (currentState == LOW && lastButtonStates[i] == HIGH) {
      relayStates[i] = !relayStates[i];
      digitalWrite(relayPins[i], relayStates[i] ? HIGH : LOW);
      
      // Send sync back to ESP8266
      Serial.print("S");
      Serial.print(i);
      Serial.println(relayStates[i] ? "0" : "1");
      
      delay(200); // Debounce
    }
    lastButtonStates[i] = currentState;
  }
}

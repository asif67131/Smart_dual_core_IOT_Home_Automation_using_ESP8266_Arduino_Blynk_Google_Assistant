#include <Servo.h>

Servo doorHinge;
const int relayPins[] = {2, 3, 4, 5}; // R0=D2, R1=D3, R2=D4(Solenoid), R3=D5(Light)
const int servoPin = 10;
const int statusLed = A4;

void setup() {
  Serial.begin(9600);
  doorHinge.attach(servoPin);
  pinMode(statusLed, OUTPUT);
  
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Relays OFF (Active Low)
  }
  doorHinge.write(0); // Initial Closed Position
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    // Individual Light 1 & 2
    if (command == "R0_ON") digitalWrite(relayPins[0], LOW);
    if (command == "R0_OFF") digitalWrite(relayPins[0], HIGH);
    if (command == "R1_ON") digitalWrite(relayPins[1], LOW);
    if (command == "R1_OFF") digitalWrite(relayPins[1], HIGH);

    // DOOR MASTER LOGIC
    if (command == "DOOR_OPEN") {
      digitalWrite(relayPins[3], LOW);    // Turn Light 3 (Door Light) ON
      digitalWrite(relayPins[2], LOW);    // Unlock Solenoid
      delay(800);                         // Wait for latch to pull back
      doorHinge.write(90);                // Move Servo to 90
      delay(4200);                        // Total 5s open time for solenoid
      digitalWrite(relayPins[2], HIGH);   // Lock Solenoid (stays locked while door is open)
      visualFeedback();
    } 
    else if (command == "DOOR_CLOSE") {
      doorHinge.write(0);                 // Move Servo back to 0
      digitalWrite(relayPins[3], HIGH);   // Turn Light 3 OFF
      // Note: Solenoid (Relay 2) is NOT touched. 
      // It remains locked so the door latches shut.
      visualFeedback();
    }
  }
}

void visualFeedback() {
  digitalWrite(statusLed, HIGH); delay(2000); digitalWrite(statusLed, LOW);
}
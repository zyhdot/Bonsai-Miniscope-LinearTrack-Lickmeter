/*
 * Lickometer with State-Change Detection and External Pull-up Resistors
 *
 * Hardware Requirements:
 * - Left Side: A 10MΩ resistor is connected between Pin 2 and 5V. The lick spout is connected to Pin 2.
 * - Right Side: A 10MΩ resistor is connected between Pin 3 and 5V. The lick spout is connected to Pin 3.
 * - The metal floor plate is connected to GND.
 *
 * Functionality:
 * - Utilizes high-resistance external pull-up resistors to significantly increase detection sensitivity.
 * - Sends serial messages only at the start and end of a lick action to avoid flooding the serial monitor and ensure clear output.
 */

// --- Pin Definitions ---
const int leftLickPin = 2;
const int rightLickPin = 3;
const int leftOutputPin = 8;
const int rightOutputPin = 9;

// --- Variables for State-Change Detection ---
// Stores the pin state from the previous loop, initialized to HIGH (not licking)
int lastLeftLickState = HIGH;
int lastRightLickState = HIGH;

// --- Mandatory setup function ---
void setup() {
  Serial.begin(9600);
  Serial.println("Lickometer Initialized (High Sensitivity Mode). Waiting for lick...");

  // --- Configure Pin Modes ---
  // Must be set to INPUT mode because we are using external pull-up resistors
  pinMode(leftLickPin, INPUT);
  pinMode(rightLickPin, INPUT);

  // Output pin settings remain unchanged
  pinMode(leftOutputPin, OUTPUT);
  pinMode(rightOutputPin, OUTPUT);

  // Ensure no 5V signal is output in the initial state
  digitalWrite(leftOutputPin, LOW);
  digitalWrite(rightOutputPin, LOW);
}

// --- Mandatory loop function ---
void loop() {
  // --- Left Lick Detection ---
  int currentLeftLickState = digitalRead(leftLickPin);

  // Check if the current state is different from the last one
  if (currentLeftLickState != lastLeftLickState) {
    // If the state has changed and it's from HIGH to LOW (lick started)
    if (currentLeftLickState == LOW) {
      digitalWrite(leftOutputPin, HIGH);
      Serial.println("Left Lick STARTED"); // Print only once at the start
    }
    // If it's from LOW to HIGH (lick stopped)
    else {
      digitalWrite(leftOutputPin, LOW);
      Serial.println("Left Lick STOPPED"); // Print once when it stops
    }
    // Update the last state to prepare for the next comparison
    lastLeftLickState = currentLeftLickState;
  }

  // --- Right Lick Detection (same logic as above) ---
  int currentRightLickState = digitalRead(rightLickPin);

  if (currentRightLickState != lastRightLickState) {
    if (currentRightLickState == LOW) {
      digitalWrite(rightOutputPin, HIGH);
      Serial.println("Right Lick STARTED");
    } else {
      digitalWrite(rightOutputPin, LOW);
      Serial.println("Right Lick STOPPED");
    }
    // Update the last state to prepare for the next comparison
    lastRightLickState = currentRightLickState;
  }
}
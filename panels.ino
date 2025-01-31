#include <Servo.h>

// Define LDR pins
const int ldrPins[] = {A5, A4, A3, A2, A1}; // Analog pins for LDRs
const int numLDRs = 5; // Number of LDRs

// Define servo pins
const int servoPins[] = {2, 3, 4}; // Digital pins for servos
const int numServos = 3; // Number of servos

// Define tolerance for LDR reading
const int light_threshold = 500; // Adjust this value based on your LDR sensitivity

// Create servo objects
Servo servos[numServos];

// Initial and final positions for servos
int initialPositions[] = {50, 65, 110}; // Initial positions (e.g., 90 degrees)
int finalPositions[] = {100, 100, 70}; // Final positions (e.g., 180 degrees)

void setup() {
  // Attach servos to their respective pins
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(initialPositions[i]); // Move servos to initial positions
  }

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  bool shouldRotate = false;

  // Check each LDR
  for (int i = 0; i < numLDRs; i++) {
    int ldrValue = analogRead(ldrPins[i]); // Read LDR value
    Serial.print("LDR ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(ldrValue);

    // If any LDR reading is above the tolerance, set the flag to rotate servos
    if (ldrValue > light_threshold) {
      shouldRotate = true;
      break; // Exit the loop as soon as one LDR exceeds the tolerance
    }
  }

  // Rotate servos if any LDR exceeds the tolerance
  if (shouldRotate) {
    for (int i = 0; i < numServos; i++) {
      servos[i].write(finalPositions[i]); // Move servos to final positions
    }
    Serial.println("Servos rotated to final positions!");
  } else {
    for (int i = 0; i < numServos; i++) {
      servos[i].write(initialPositions[i]); // Move servos back to initial positions
    }
    Serial.println("Servos returned to initial positions.");
  }

  delay(20); // Add a small delay to avoid rapid toggling
}
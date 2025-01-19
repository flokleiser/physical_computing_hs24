
#include <Arduino.h>

// Define pins
const int encoderPinA = 2;  // Signal A
const int encoderPinB = 3;  // Signal B
const int buttonPin = 4;    // Button (optional)

// Variables for encoder position and state
int encoderPosition = 0;    // Tracks rotation position
int lastState = 0;          // Previous state (combination of A and B)
int currentState;           // Current state (combination of A and B)

unsigned long lastDebounceTime = 0; // Time for debouncing
const unsigned long debounceDelay = 5; // Debounce time in milliseconds

void setup() {
  // Configure pins
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Rotary Encoder Test Ready");

  // Initialize lastState with the initial state of the encoder
  int signalA = digitalRead(encoderPinA);
  int signalB = digitalRead(encoderPinB);
  lastState = (signalA << 1) | signalB; // Combine A and B into a single state
}

void loop() {
  // Read the current state of Signal A and Signal B
  int signalA = digitalRead(encoderPinA);
  int signalB = digitalRead(encoderPinB);
  currentState = (signalA << 1) | signalB; // Combine A and B into a single state

  // Check for state changes with debounce
  if (millis() - lastDebounceTime > debounceDelay) {
    if (currentState != lastState) {
      // Detect valid state transitions for clockwise and counterclockwise rotation
      if (lastState == 0b00 && currentState == 0b01) encoderPosition++; // Clockwise
      else if (lastState == 0b01 && currentState == 0b11) encoderPosition++;
      else if (lastState == 0b11 && currentState == 0b10) encoderPosition++;
      else if (lastState == 0b10 && currentState == 0b00) encoderPosition++;

      else if (lastState == 0b00 && currentState == 0b10) encoderPosition--; // Counterclockwise
      else if (lastState == 0b10 && currentState == 0b11) encoderPosition--;
      else if (lastState == 0b11 && currentState == 0b01) encoderPosition--;
      else if (lastState == 0b01 && currentState == 0b00) encoderPosition--;

      // Update the last state
      lastState = currentState;
      lastDebounceTime = millis(); // Reset debounce timer

      // Print the current position
      Serial.print("Current Position: ");
      Serial.println(encoderPosition);
    }
  }

  // Check for button press
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button Pressed");
    delay(200); // Debounce for button press
  }
}


// // Define pins
// const int encoderPinA = 2;  // Pin for signal A
// const int encoderPinB = 3;  // Pin for signal B
// const int buttonPin = 4;    // Pin for button (if available)

// // Variables to track encoder state
// int lastEncoderAState = LOW;
// int currentEncoderAState;

// // Setup
// void setup() {
//   // Configure pins
//   pinMode(encoderPinA, INPUT_PULLUP);
//   pinMode(encoderPinB, INPUT_PULLUP);
//   pinMode(buttonPin, INPUT_PULLUP);

//   // Initialize Serial Monitor
//   Serial.begin(9600);

//   // Initialize encoder state
//   lastEncoderAState = digitalRead(encoderPinA);

//   Serial.println("Rotary Encoder Test Ready");
// }

// // Loop
// void loop() {
//   // Read the current state of encoderPinA
//   currentEncoderAState = digitalRead(encoderPinA);

//   // Check for a change in state
//   if (currentEncoderAState != lastEncoderAState) {
//     // Read the state of encoderPinB
//     int encoderBState = digitalRead(encoderPinB);

//     // Determine rotation direction
//     if (currentEncoderAState == HIGH) {
//       if (encoderBState == LOW) {
//         Serial.println("Rotated Clockwise");
//       } else {
//         Serial.println("Rotated Counterclockwise");
//       }
//     }
//     lastEncoderAState = currentEncoderAState;
//   }

//   // Check if the button is pressed
//   if (digitalRead(buttonPin) == LOW) {
//     Serial.println("Button Pressed");
//     delay(200);  // Debounce delay
//   }
// }

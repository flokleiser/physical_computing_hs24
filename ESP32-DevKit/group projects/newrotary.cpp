#include <Arduino.h>

// Define pins
const int encoderPinA = 2;  
const int encoderPinB = 3;  
const int buttonPin = 4;    
const int motorPin = 10;

int encoderPosition = 0;    
int lastState = 0;          
int currentState;           

unsigned long lastDebounceTime = 0; 
const unsigned long debounceDelay = 5;

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
      lastDebounceTime = millis();

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


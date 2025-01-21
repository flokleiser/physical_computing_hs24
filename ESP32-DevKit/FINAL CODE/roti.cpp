#include <Arduino.h>
#include <USB.h>
#include <USBHIDConsumerControl.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>

// Rotary encoder pins
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 5
#define BUTTON_PIN 4

// Rotary encoder state
int lastState = 0;
int encoderPosition = 0;

// USB HID consumer control object
USBHIDConsumerControl ConsumerControl;
USBHIDKeyboard Keyboard;    
USBHIDMouse Mouse;

// Counter for fine scrolling
float scrollAccumulator = 0.0;

void setup() {
    // Initialize USB HID
    ConsumerControl.begin();
    USB.begin();
    Mouse.begin();
    Keyboard.begin();

    // Initialize rotary encoder pins
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Serial monitor for debugging
    Serial.begin(9600);
    Serial.println("Rotary Encoder USB HID Scrolling Ready");
}

//
void WebModeRoti() {
    // Read encoder state
    int signalA = digitalRead(ENCODER_PIN_A);
    int signalB = digitalRead(ENCODER_PIN_B);

    // Combine signals into a single state
    int currentState = (signalA << 1) | signalB;

    // Detect rotation
    if (currentState != lastState) {
        if ((lastState == 0b00 && currentState == 0b01) ||  // Clockwise
            (lastState == 0b01 && currentState == 0b11) ||
            (lastState == 0b11 && currentState == 0b10) ||
            (lastState == 0b10 && currentState == 0b00)) {
            scrollAccumulator += 0.1; // Increment scroll accumulator
            if (scrollAccumulator >= 1.0) {
                Mouse.move(0, 0, 1); // Scroll up
                scrollAccumulator -= 1.0;
                Serial.println("Scroll Up");
            }
        } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
                   (lastState == 0b10 && currentState == 0b11) ||
                   (lastState == 0b11 && currentState == 0b01) ||
                   (lastState == 0b01 && currentState == 0b00)) {
            scrollAccumulator -= 0.1; // Decrement scroll accumulator
            if (scrollAccumulator <= -1.0) {
                Mouse.move(0, 0, -1); // Scroll down
                scrollAccumulator += 1.0;
                Serial.println("Scroll Down");
            }
        }

        lastState = currentState; // Update the last state
    }

    // Optional: Check for button press
    if (digitalRead(BUTTON_PIN) == LOW) {
        Serial.println("Button Pressed");
        delay(200); // Simple debounce
    }

    delay(1); // Short delay for stability
}

void AudioModeRoti() {
    // Read encoder state
    int signalA = digitalRead(ENCODER_PIN_A);
    int signalB = digitalRead(ENCODER_PIN_B);

    // Combine signals into a single state
    int currentState = (signalA << 1) | signalB;

    // Detect rotation
    if (currentState != lastState) {
        if ((lastState == 0b00 && currentState == 0b01) ||  // Clockwise
            (lastState == 0b01 && currentState == 0b11) ||
            (lastState == 0b11 && currentState == 0b10) ||
            (lastState == 0b10 && currentState == 0b00)) {
            scrollAccumulator += 0.1; // Increment scroll accumulator
            if (scrollAccumulator >= 1.0) {
                Mouse.move(0, 0, 1); // Scroll up
                scrollAccumulator -= 1.0;
                Serial.println("Scroll Up");
            }
        } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
                   (lastState == 0b10 && currentState == 0b11) ||
                   (lastState == 0b11 && currentState == 0b01) ||
                   (lastState == 0b01 && currentState == 0b00)) {
            scrollAccumulator -= 0.1; // Decrement scroll accumulator
            if (scrollAccumulator <= -1.0) {
                Mouse.move(0, 0, -1); // Scroll down
                scrollAccumulator += 1.0;
                Serial.println("Scroll Down");
            }
        }

        lastState = currentState; // Update the last state
    }

    // Optional: Check for button press
    if (digitalRead(BUTTON_PIN) == LOW) {
        Serial.println("Button Pressed");
        delay(200); // Simple debounce
    }

    delay(1); // Short delay for stability
}


//Select elements
void MacModeRoti() {
    // Read encoder state
    int signalA = digitalRead(ENCODER_PIN_A);
    int signalB = digitalRead(ENCODER_PIN_B);

    // Combine signals into a single state
    int currentState = (signalA << 1) | signalB;

    // Detect rotation
    if (currentState != lastState) {
        if ((lastState == 0b00 && currentState == 0b01) ||  // Clockwise
            (lastState == 0b01 && currentState == 0b11) ||
            (lastState == 0b11 && currentState == 0b10) ||
            (lastState == 0b10 && currentState == 0b00)) {
            scrollAccumulator += 0.1; // Increment scroll accumulator
            if (scrollAccumulator >= 1.0) {
                Keyboard.press(KEY_TAB);
                Keyboard.releaseAll();
            }
        } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
                   (lastState == 0b10 && currentState == 0b11) ||
                   (lastState == 0b11 && currentState == 0b01) ||
                   (lastState == 0b01 && currentState == 0b00)) {
            scrollAccumulator -= 0.1; // Decrement scroll accumulator
            if (scrollAccumulator <= -1.0) {
                Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press(KEY_TAB);
                Keyboard.releaseAll();
            }
        }

        lastState = currentState; // Update the last state
    }

    // Optional: Check for button press
    if (digitalRead(BUTTON_PIN) == LOW) {
        Serial.println("Button Pressed");
        delay(200); // Simple debounce
    }

    delay(1); // Short delay for stability
}

#include <Arduino.h>
#include <USB.h>
#include <USBHIDConsumerControl.h>
#include <USBHIDMouse.h>
#include <USBHIDKeyboard.h>

// Rotary encoder pins
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 5
#define BUTTON_PIN 4

// Rotary encoder state
int lastState = 0;
int encoderPosition = 0;

bool mode = false;

// USB HID consumer control object
USBHIDConsumerControl ConsumerControl;
USBHIDRelativeMouse Mouse;
USBHIDKeyboard Keyboard;    

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

// //scroll
// // void loop() {
//     // Read encoder state

// //  if (bool) {

//     int signalA = digitalRead(ENCODER_PIN_A);
//     int signalB = digitalRead(ENCODER_PIN_B);

//     // Combine signals into a single state
//     int currentState = (signalA << 1) | signalB;

//     // Detect rotation
//     if (currentState != lastState) {
//         if ((lastState == 0b00 && currentState == 0b01) ||  // Clockwise
//             (lastState == 0b01 && currentState == 0b11) ||
//             (lastState == 0b11 && currentState == 0b10) ||
//             (lastState == 0b10 && currentState == 0b00)) {
//             // Reverse direction: scroll down on clockwise rotation
//             scrollAccumulator -= 1.0; // Decrement scroll accumulator
//             if (scrollAccumulator <= -1.0) {
//                 Mouse.move(0, 0, -1); // Scroll down
//                 scrollAccumulator += 1.0;
//                 Serial.println("Scroll Down");
//             }
//         } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
//                    (lastState == 0b10 && currentState == 0b11) ||
//                    (lastState == 0b11 && currentState == 0b01) ||
//                    (lastState == 0b01 && currentState == 0b00)) {
//             // Reverse direction: scroll up on counterclockwise rotation
//             scrollAccumulator += 1.0; // Increment scroll accumulator
//             if (scrollAccumulator >= 1.0) {
//                 Mouse.move(0, 0, 1); // Scroll up
//                 scrollAccumulator -= 1.0;
//                 Serial.println("Scroll Up");
//             }
//         }

//         lastState = currentState; // Update the last state
//     }

//     // Optional: Check for button press
//     if (digitalRead(BUTTON_PIN) == LOW) {
//         Serial.println("Button Pressed");
//         delay(200); // Simple debounce
//     }

//     delay(1); // Short delay for stability
// }


//tabs switcher

void loop() {
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
            scrollAccumulator -= 1.0; // Decrement scroll accumulator
            if (scrollAccumulator <= -1.0) {

                // Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press(KEY_TAB);
                delay(50);
                Keyboard.releaseAll();

                scrollAccumulator += 1.0;
                Serial.println("Scroll Down");
            }
        } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
                   (lastState == 0b10 && currentState == 0b11) ||
                   (lastState == 0b11 && currentState == 0b01) ||
                   (lastState == 0b01 && currentState == 0b00)) {
            scrollAccumulator += 1.0; // Increment scroll accumulator
            if (scrollAccumulator >= 1.0) {

                Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press(KEY_TAB);
                delay(50);
                Keyboard.releaseAll();

                scrollAccumulator -= 1.0;
                Serial.println("Scroll Up");
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


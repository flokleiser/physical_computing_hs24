// #include <Arduino.h>
// #include <USB.h>
// #include <USBHIDConsumerControl.h>
// #include <USBHIDMouse.h>

// // Rotary encoder pins
// #define ENCODER_PIN_A 2
// #define ENCODER_PIN_B 5
// #define BUTTON_PIN 4

// // Rotary encoder state
// int lastState = 0;
// int encoderPosition = 0;

// // USB HID consumer control object
// USBHIDConsumerControl ConsumerControl;
// USBHIDRelativeMouse Mouse;

// void setup() {
//     // Initialize USB HID
//     ConsumerControl.begin();
//     USB.begin();
//     Mouse.begin();

//     // Initialize rotary encoder pins
//     pinMode(ENCODER_PIN_A, INPUT_PULLUP);
//     pinMode(ENCODER_PIN_B, INPUT_PULLUP);
//     pinMode(BUTTON_PIN, INPUT_PULLUP);

//     // Serial monitor for debugging
//     Serial.begin(9600);
//     Serial.println("Rotary Encoder USB HID Scrolling Ready");
// }

// void loop() {
//     // Read encoder state
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
//             encoderPosition++;
//             Serial.println("Scroll Up");
//             // ConsumerControl.press(MEDIA_VOLUME_UP);
//             // ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
//             Mouse.move(0, 0, 1); 
//             // delay(500);
//             delay(10); // Delay to debounce
//             ConsumerControl.release();
//         } else if ((lastState == 0b00 && currentState == 0b10) ||  // Counterclockwise
//                    (lastState == 0b10 && currentState == 0b11) ||
//                    (lastState == 0b11 && currentState == 0b01) ||
//                    (lastState == 0b01 && currentState == 0b00)) {
//             encoderPosition--;
//             Serial.println("Scroll Down");
//             // ConsumerControl.press(MEDIA_VOLUME_DOWN);
//             // ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
//             // delay(10); // Delay to debounce
//              Mouse.move(0, 0, -1);
//             // delay(500);
//             ConsumerControl.release();
//         }

//         lastState = currentState; // Update the last state
//     }

//     // Optional: Check for button press
//     if (digitalRead(BUTTON_PIN) == LOW) {
//         Serial.println("Button Pressed");
//         // ConsumerControl.press(MEDIA_PLAY_PAUSE); // Example: Play/Pause
//         delay(200);                              // Simple debounce
//         ConsumerControl.release();
//     }

//     delay(1); // Short delay for stability
// }

#include <Arduino.h>
#include <USB.h>
#include <USBHIDConsumerControl.h>
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
USBHIDRelativeMouse Mouse;

// Counter for fine scrolling
float scrollAccumulator = 0.0;

void setup() {
    // Initialize USB HID
    ConsumerControl.begin();
    USB.begin();
    Mouse.begin();

    // Initialize rotary encoder pins
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Serial monitor for debugging
    Serial.begin(9600);
    Serial.println("Rotary Encoder USB HID Scrolling Ready");
}

void loop() {
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

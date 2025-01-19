//TODO: BROWSERTABS,MEDIATIMELINE,CMDTAB


#include <Arduino.h>
#include <USB.h>
#include <USBHIDConsumerControl.h>
#include <USBHIDMouse.h>
#include <USBHIDKeyboard.h>

#define POT 10

USBHIDConsumerControl ConsumerControl;
USBHIDRelativeMouse Mouse;
USBHIDKeyboard Keyboard;    

int potValue = 0;
int mappedPotValue = 0;
int numTabs = 9;

int prevPotValue = 0; 
int threshold = 10; 

void setup() {
    Serial.begin(9600);
    pinMode(POT, INPUT);

    ConsumerControl.begin();
    USB.begin();
    Mouse.begin();
    Keyboard.begin();
}

//boilerplate
// void loop() {
//     potValue = analogRead(POT);
//     Serial.println(potValue);
//     delay(100);
// }

//web mode
void loop() {
    potValue = analogRead(POT);
    delay(100);

    mappedPotValue = map(potValue, 0, 1023, 0, numTabs);
    // Keyboard.press(KEY_LEFT_GUI);
    switch(mappedPotValue) {
        case 0:
            Keyboard.press('1');
            Serial.println('1');
            break;
        case 1:
            Keyboard.press('2');
            Serial.println('2');
            break;
        case 2:
            Keyboard.press('3');
            Serial.println('3');
            break;
        case 3:
            Keyboard.press('4');
            Serial.println('4');
            break;
        case 4:
            Keyboard.press('5');
            Serial.println('5');
            break;
        case 5:
            Keyboard.press('6');
            Serial.println('6');
            break;
        case 6:
            Keyboard.press('7');
            Serial.println('7');
            break;
        case 7:
            Keyboard.press('8');
            Serial.println('8');
            break;
        case 8:
            Keyboard.press('9');
            Serial.println('9');
            break;
    }
    Keyboard.releaseAll();
}

//mac mode
// void loop() {
//     if (abs(potValue - prevPotValue) > threshold) {
//         if (potValue > prevPotValue) {
//             // Potentiometer is increasing
//             Keyboard.press(KEY_LEFT_GUI);
//             Keyboard.press(KEY_TAB);
//             delay(10); // Small delay to ensure the press is registered
//             Keyboard.releaseAll();
//             Serial.println("Command + Tab"); // Debug print (optional)
//         } else if (potValue < prevPotValue) {
//             // Potentiometer is decreasing
//             Keyboard.press(KEY_LEFT_GUI);
//             Keyboard.press(KEY_LEFT_SHIFT);
//             Keyboard.press(KEY_TAB);
//             delay(10); // Small delay to ensure the press is registered
//             Keyboard.releaseAll();
//             Serial.println("Shift + Command + Tab"); // Debug print (optional)
//         }

//         // Update the previous potentiometer value
//         prevPotValue = potValue;
//     }

//     delay(100); // Adjust the loop speed as necessary
// }

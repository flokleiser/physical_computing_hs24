#include <Arduino.h>
#include <USB.h>
#include <USBHIDConsumerControl.h>
#include <USBHIDMouse.h>
#include <USBHIDKeyboard.h>

#define potPIN 16

USBHIDConsumerControl ConsumerControl;
USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;   

const int threshold = 1;     
const int numSteps = 10;     
const int delayTime = 10;    
const int loopDelay = 100;  

int potValue = 0;            
int prevPotValue = 0;        
int mappedValue = 0;         
int prevMappedValue = 0;   
int mappedPotValue = 0;
int numTabs = 9;

void setup() {
    Serial.begin(9600);
    pinMode(potPIN, INPUT);
     
    prevPotValue = analogRead(potPIN); 
    prevMappedValue = map(prevPotValue, 0, 4094, 1, numSteps);

    Keyboard.begin();
    ConsumerControl.begin();
    USB.begin();
    Mouse.begin();
}

//cmd + tab switcher 
void MACModeSlider() {
  potValue = analogRead(potPIN);
  
  mappedValue = map(potValue, 0, 4094, 1, numSteps);

  if (mappedValue != prevMappedValue) {
    if (mappedValue > prevMappedValue) {
      
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_TAB);
      Keyboard.press('1');
      delay(delayTime);
      Keyboard.releaseAll(); 
      Serial.println("Command + Tab");
    } else if (mappedValue < prevMappedValue) {
     
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('1');
      Serial.println("Shift + Command + Tab"); 
    }

    prevMappedValue = mappedValue;
  }
  delay(loopDelay);
}




//web mode, tab switcher -> have to change cmd 1 to prev tab and cmd 2 to next tab
void WebModeSlider() {
    potValue = analogRead(potPIN);
    delay(100);

    mappedPotValue = map(potValue, 0, 4095, 0, numTabs);

  if (mappedValue != prevMappedValue) {
    
    Keyboard.press(KEY_LEFT_GUI);
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

        prevMappedValue = mappedValue;
    }
}




//!!!!!!!!!!!!!PLACEHOLDER
void AudioModeSlider() {
    potValue = analogRead(potPIN);
    delay(100);

    mappedPotValue = map(potValue, 0, 4095, 0, numTabs);

  if (mappedValue != prevMappedValue) {
    
    Keyboard.press(KEY_LEFT_GUI);
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

        prevMappedValue = mappedValue;
    }
}
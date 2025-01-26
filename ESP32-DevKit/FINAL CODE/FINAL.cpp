#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <USB.h>
#include <USBHIDConsumerControl.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>

// MODESTATE
int modeState = 1;

// SWITCH
#define PIN_NEOPIXEL 10 
#define NUMPIXELSLEDSTRIP 8    
#define SWITCH_POWER_PIN 1  
#define SWITCH_MODE_PIN_1 8 
#define SWITCH_MODE_PIN_2 9  

// BUTTONS
#define NUMPIXELSBUTTON 1
#define PINLedRight 4
#define PINRight 2
#define PINLedMiddle 6
#define PINMiddle 5
#define PINLedLeft 21
#define PINLeft 7

// POTI
#define NUMPIXELSLEDRING 12
#define PINPoti 14
#define PINLedRing 15

// ROTI
#define ENCODER_PIN_A 42
#define ENCODER_PIN_B 43
//#define BUTTON_PIN 4

// SLIDER
#define potPIN 16

// BUTTON LED
Adafruit_NeoPixel pixelRight(NUMPIXELSBUTTON, PINLedRight, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelMiddle(NUMPIXELSBUTTON, PINLedMiddle, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelLeft(NUMPIXELSBUTTON, PINLedLeft, NEO_GRB + NEO_KHZ800);

// POTI LED
Adafruit_NeoPixel pixelPOTI(NUMPIXELSLEDRING, PINLedRing, NEO_GRB + NEO_KHZ800);

// SWITCH LED
Adafruit_NeoPixel pixelsMother(NUMPIXELSLEDSTRIP, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// SWITCH VARIABLES
bool lastPowerState = false;

// BUTTON VARIABLES
bool prevStateRight = HIGH;
bool prevStateMiddle = HIGH;
bool prevStateLeft = HIGH;

// POTI VARIABLES
int potiValue = 0;         
int parsedPotiValue = 0;  
int lastPotiValue = -1;   
int parsedLedValue = 0;

// ROTI VARIABLES
int lastState = 0;
int encoderPosition = 0;
float scrollAccumulator = 0.0;

// SLIDER VARIABLES
const int threshold = 1;     // Minimum change to detect movement
const int numSteps = 10;     // Number of steps to map the potentiometer range
const int delayTime = 10;    // Small delay for keypress registration
const int loopDelay = 100;  
int potValue = 0;            // Current potentiometer value
int prevPotValue = 0;        // Previous potentiometer value
int mappedValue = 0;         // Mapped value from 1 to 10
int prevMappedValue = 0;   
int mappedPotValue = 0;
int numTabs = 9;

// ALLGEMEIN
USBHIDConsumerControl ConsumerControl;
USBHIDKeyboard Keyboard;
USBHIDMouse Mouse;



void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

    // SWITCH
    pinMode(SWITCH_POWER_PIN, INPUT_PULLUP); 
    pinMode(SWITCH_MODE_PIN_1, INPUT_PULLUP); 
    pinMode(SWITCH_MODE_PIN_2, INPUT_PULLUP); 
    pixelsMother.begin();
    pixelsMother.clear(); 
    pixelsMother.show();

    // BUTTON
    pinMode(PINLeft, INPUT_PULLUP);
    pinMode(PINMiddle, INPUT_PULLUP);
    pinMode(PINRight, INPUT_PULLUP);
    pixelLeft.begin();
    pixelMiddle.begin();
    pixelRight.begin();

    // POTI 
    pinMode(PINPoti, INPUT);
    pixelPOTI.begin();
    pixelPOTI.clear();
    pixelPOTI.show();

    // ROTI
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    //pinMode(BUTTON_PIN, INPUT_PULLUP);

    // SLIDER
    pinMode(potPIN, INPUT);
    prevPotValue = analogRead(potPIN); 
    prevMappedValue = map(prevPotValue, 0, 4094, 1, numSteps);


    // ALLGEMEIN
    USB.begin();
    ConsumerControl.begin();
    Keyboard.begin();
    Mouse.begin();

}

void loop() {
  //int OnOff = digitalRead(SWITCH_POWER_PIN);
  OnOFF();
    if(modeState == 1){
    WebModeButton();
    WebModePoti();
    //WebModeRoti();
    //WebModeSlider();
  } else if (modeState == 2) {
    MACModeButton();
    MACModePoti();
    //MacModeRoti();
    //MACModeSlider();
  } else if (modeState == 3) {
    AudioModeButton();
    AudioModePoti();
    //AudioModeRoti();
    //AudioModeSlider();
  }
  
}

void OnOFF(){
  bool powerState = digitalRead(SWITCH_POWER_PIN) == LOW; 

  if (powerState) {
        if (!lastPowerState) {
            Serial.println("Switch ON - Animation startet");
            playAnimation();
        }

        if (digitalRead(SWITCH_MODE_PIN_1) == HIGH && digitalRead(SWITCH_MODE_PIN_2) == LOW) {
            Serial.println("Mode Web");
            showMode(6, 7, pixelsMother.Color(100, 0, 100)); 
            modeState = 1;
        } else if (digitalRead(SWITCH_MODE_PIN_1) == LOW && digitalRead(SWITCH_MODE_PIN_2) == HIGH) {
            Serial.println("Mode Mac");
            showMode(2, 3, pixelsMother.Color(100, 0, 100)); 
            modeState = 3;
        } else if (digitalRead(SWITCH_MODE_PIN_1) == HIGH && digitalRead(SWITCH_MODE_PIN_2) == HIGH) {
            Serial.println("Mode Media");
            showMode(4, 5, pixelsMother.Color(100, 0, 100)); 
            modeState = 2;
        } else {
            Serial.println("Switches in invalid state - Alle LEDs aus");
            pixelsMother.clear();
            pixelsMother.show();
        }
    } else {
        Serial.println("Switch OFF - Alle LEDs aus");
        pixelsMother.clear();
        pixelsMother.show();

        pixelPOTI.clear();
        pixelPOTI.show();
    }

    lastPowerState = powerState;

    delay(50);
}

void playAnimation() {
    for (int i = 0; i < NUMPIXELSLEDSTRIP; i++) {
        pixelsMother.setPixelColor(i, pixelsMother.Color(100, 0, 100)); 
        pixelsMother.show();
        delay(100);
    }

    for (int i = NUMPIXELSLEDSTRIP - 1; i >= 0; i--) {
        pixelsMother.setPixelColor(i, pixelsMother.Color(0, 0, 0));
        pixelsMother.show();
        delay(100);
    }
}

void showMode(int led1, int led2, uint32_t color) {
    pixelsMother.clear(); 
    pixelsMother.setPixelColor(led1, color); 
    pixelsMother.setPixelColor(led2, color);
    pixelsMother.show(); 
}

// BUTTONS -------------------------------------------------------------------------------------
void WebModeButton(){
  pixelLeft.clear();
  pixelMiddle.clear();
  pixelRight.clear();

  bool currentStateRight = digitalRead(PINRight);
  bool currentStateMiddle = digitalRead(PINMiddle);
  bool currentStateLeft = digitalRead(PINLeft);

  if (currentStateRight == LOW && prevStateRight == HIGH) {
    Keyboard.press(KEY_LEFT_GUI);  // Command-Taste
    Keyboard.press('r');           // "R"-Taste
    delay(50);                     // Kurze Verzögerung
    Keyboard.releaseAll();
  }

  if (currentStateRight == LOW) {
    pixelRight.setPixelColor(0, pixelRight.Color(100, 0, 100));
  } else {
    pixelRight.setPixelColor(0, pixelRight.Color(0, 0, 0));
  }

  if (currentStateMiddle == LOW && prevStateMiddle == HIGH) {
    Keyboard.press(KEY_LEFT_GUI);    // Command-Taste
    Keyboard.press(KEY_LEFT_ARROW);  // Pfeil links
    delay(50);
    Keyboard.releaseAll();
  }

  if (currentStateMiddle == LOW) {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(100, 0, 100));
  } else {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(0, 0, 0));
  }

  if (currentStateLeft == LOW && prevStateLeft == HIGH) {
    Keyboard.press(KEY_LEFT_GUI);  // Command-Taste
    Keyboard.press('t');           // "T"-Taste
    delay(50);
    Keyboard.releaseAll();
  }

  if (currentStateLeft == LOW) {
    pixelLeft.setPixelColor(0, pixelLeft.Color(100, 0, 100));
  } else {
    pixelLeft.setPixelColor(0, pixelLeft.Color(0, 0, 0));
  }

  pixelLeft.show();
  pixelMiddle.show();
  pixelRight.show();

  prevStateRight = currentStateRight;
  prevStateMiddle = currentStateMiddle;
  prevStateLeft = currentStateLeft;
}

void MACModeButton(){
  pixelLeft.clear();
  pixelMiddle.clear();
  pixelRight.clear();

  bool currentStateRight = digitalRead(PINRight);
  bool currentStateMiddle = digitalRead(PINMiddle);
  bool currentStateLeft = digitalRead(PINLeft);

  if (currentStateRight == LOW && prevStateRight == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press(KEY_LEFT_GUI); // Command-Taste
    Keyboard.press('q');           // "R"-Taste
    delay(50);                     // Kurze Verzögerung
    Keyboard.releaseAll();
  }

  if (currentStateRight == LOW) {
    pixelRight.setPixelColor(0, pixelRight.Color(100, 0, 100));
  } else {
    pixelRight.setPixelColor(0, pixelRight.Color(0, 0, 0));
  }

  if (currentStateMiddle == LOW && prevStateMiddle == HIGH) {
    Keyboard.press(KEY_LEFT_SHIFT);    // Command-Taste
    Keyboard.press(KEY_F12);  // Pfeil links
    delay(50);
    Keyboard.releaseAll();
  }

  if (currentStateMiddle == LOW) {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(100, 0, 100));
  } else {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(0, 0, 0));
  }

  if (currentStateLeft == LOW && prevStateLeft == HIGH) {
    Keyboard.press(KEY_F11);  // Command-Taste
    delay(50);
    Keyboard.releaseAll();
  }

  if (currentStateLeft == LOW) {
    pixelLeft.setPixelColor(0, pixelLeft.Color(100, 0, 100));
  } else {
    pixelLeft.setPixelColor(0, pixelLeft.Color(0, 0, 0));
  }

  pixelLeft.show();
  pixelMiddle.show();
  pixelRight.show();

  prevStateRight = currentStateRight;
  prevStateMiddle = currentStateMiddle;
  prevStateLeft = currentStateLeft;
}

void AudioModeButton(){
  pixelLeft.clear();
  pixelMiddle.clear();
  pixelRight.clear();

  bool currentStateRight = digitalRead(PINRight);
  bool currentStateMiddle = digitalRead(PINMiddle);
  bool currentStateLeft = digitalRead(PINLeft);

  if (currentStateRight == LOW && prevStateRight == HIGH) {
    ConsumerControl.press(CONSUMER_CONTROL_PLAY_PAUSE);
    delay(10);  // Delay to debounce
    ConsumerControl.release();
  }

  if (currentStateRight == LOW) {
    pixelRight.setPixelColor(0, pixelRight.Color(100, 0, 100));
  } else {
    pixelRight.setPixelColor(0, pixelRight.Color(0, 0, 0));
  }

  if (currentStateMiddle == LOW && prevStateMiddle == HIGH) {
    ConsumerControl.press(CONSUMER_CONTROL_SCAN_NEXT);
    delay(10);  // Delay to debounce
    ConsumerControl.release();
  }

  if (currentStateMiddle == LOW) {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(100, 0, 100));
  } else {
    pixelMiddle.setPixelColor(0, pixelMiddle.Color(0, 0, 0));
  }

  if (currentStateLeft == LOW && prevStateLeft == HIGH) {
    ConsumerControl.press(CONSUMER_CONTROL_SCAN_PREVIOUS);
    delay(10);  // Delay to debounce
    ConsumerControl.release();
  }

  if (currentStateLeft == LOW) {
    pixelLeft.setPixelColor(0, pixelLeft.Color(100, 0, 100));
  } else {
    pixelLeft.setPixelColor(0, pixelLeft.Color(0, 0, 0));
  }
  
  pixelLeft.show();
  pixelMiddle.show();
  pixelRight.show();

  prevStateRight = currentStateRight;
  prevStateMiddle = currentStateMiddle;
  prevStateLeft = currentStateLeft;

}
// ----------------------------------------------------------------------------------------------------------

// POTI -----------------------------------------------------------------------------------------------------
void WebModePoti() {
    potiValue = analogRead(PINPoti);
    parsedPotiValue = map(potiValue, 0, 4095, 0, 16); 
    parsedLedValue = map(potiValue, 0, 4095, 0, 11);

    if (parsedPotiValue == 0) {
        pixelPOTI.clear();        // Alle LEDs löschen
        pixelPOTI.show();         // Änderungen anzeigen
    } else {
        pixelPOTI.clear();        // LEDs löschen für Neuzuweisung
        pixelPOTI.setBrightness(25);

        int numLeds = 12; // Anzahl der LEDs in Ihrem Streifen
        for (int i = 0; i <= parsedLedValue; i++) {
            int mirroredIndex = numLeds - 1 - i; // Spiegelung des Index
            pixelPOTI.setPixelColor(mirroredIndex, pixelPOTI.Color(100, 0, 100)); // Farbe setzen
        }

        pixelPOTI.show();      
    }

    // Bildschirmhelligkeit anpassen
    if (parsedPotiValue != lastPotiValue) {
        if (parsedPotiValue > lastPotiValue) {
            for (int i = 0; i < (parsedPotiValue - lastPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        } else if (parsedPotiValue < lastPotiValue) {
            for (int i = 0; i < (lastPotiValue - parsedPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        }

        lastPotiValue = parsedPotiValue;
    }

    delay(50); 
}


void MACModePoti(){
  potiValue = analogRead(PINPoti);
    parsedPotiValue = map(potiValue, 0, 4095, 0, 16); 
    parsedLedValue = map(potiValue, 0, 4095, 0, 11);

    if (parsedPotiValue == 0) {
        pixelPOTI.clear();        // Alle LEDs löschen
        pixelPOTI.show();         // Änderungen anzeigen
    } else {
        pixelPOTI.clear();        // LEDs löschen für Neuzuweisung
        pixelPOTI.setBrightness(25);

       int numLeds = 12; // Anzahl der LEDs in Ihrem Streifen
        for (int i = 0; i <= parsedLedValue; i++) {
            int mirroredIndex = numLeds - 1 - i; // Spiegelung des Index
            pixelPOTI.setPixelColor(mirroredIndex, pixelPOTI.Color(100, 0, 100)); // Farbe setzen
        }

        pixelPOTI.show();      
    }

    // Bildschirmhelligkeit anpassen
    if (parsedPotiValue != lastPotiValue) {
        if (parsedPotiValue > lastPotiValue) {
            for (int i = 0; i < (parsedPotiValue - lastPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        } else if (parsedPotiValue < lastPotiValue) {
            for (int i = 0; i < (lastPotiValue - parsedPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        }

        lastPotiValue = parsedPotiValue;
    }

    delay(50); 
}

void AudioModePoti(){
    potiValue = analogRead(PINPoti);
    parsedPotiValue = map(potiValue, 0, 4095, 0, 16); 
    parsedLedValue = map(potiValue, 0, 4095, 0, 11);

    pixelPOTI.clear();
    pixelPOTI.setBrightness(25);

    if (parsedPotiValue != lastPotiValue) {
        if (parsedPotiValue > lastPotiValue) {
            for (int i = 0; i < (parsedPotiValue - lastPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        } else if (parsedPotiValue < lastPotiValue) {
            for (int i = 0; i < (lastPotiValue - parsedPotiValue); i++) {
                ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
                delay(5); 
                ConsumerControl.release();
            }
        }

        lastPotiValue = parsedPotiValue;
    }

    int numLeds = 12; // Anzahl der LEDs in Ihrem Streifen
        for (int i = 0; i <= parsedLedValue; i++) {
            int mirroredIndex = numLeds - 1 - i; // Spiegelung des Index
            pixelPOTI.setPixelColor(mirroredIndex, pixelPOTI.Color(100, 0, 100)); // Farbe setzen
        }

    pixelPOTI.show();

    delay(50); 
}
// ----------------------------------------------------------------------------------------------------------
// ROTI -----------------------------------------------------------------------------------------------------
/*void WebModeRoti() {
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

    delay(1); // Short delay for stability
}

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

    delay(1); // Short delay for stability
}
// ----------------------------------------------------------------------------------------------------------
// SLIDER ---------------------------------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------------------------------------
*/
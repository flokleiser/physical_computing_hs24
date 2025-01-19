#include <Adafruit_NeoPixel.h>

#define NUMPIXELS    16
#define switchPin    3
#define NEOPIXEL_PIN 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 150;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

bool isFilled = false;

void setup() {
  pinMode(switchPin, INPUT);
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  int switchState = digitalRead(switchPin);
  
  if (switchState == HIGH) {
    // Serial.println("Switch ON");

    // if (!isFilled) {
        for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
            pixels.show();
            delay(delayval);
            Serial.println(i);

            // if (i == NUMPIXELS){
            //     isFilled = true;
            // }
        // }
    }
    // if (isFilled) {
        // for (int i = NUMPIXELS; i < 0; i--) {
        //     pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
        // pixels.show();
        // delay(delayval);
        // if (i == 0) {
        // isFilled = true;
        // }
    // }

  } 
  if (switchState == LOW) {

    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
        pixels.show();
        delay(delayval);
        Serial.println(i);
    }

    // pixels.clear();
    // pixels.show();
}




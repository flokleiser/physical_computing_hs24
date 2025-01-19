#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define SERVO 12 
#define LED 13
#define POT A0
#define BUTTON 2
#define NUMPIXELS 9 

Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);                                                           
Servo myservo;

int pos = 0;
int posLight = 0;
int colorInput = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {delay(1);}
  myservo.attach(SERVO);
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);
  pixels.begin(); 
}

void loop() {
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();
  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: "); Serial.println(range);
  }
  pos = map(range, 0, 180, 0, 180);
  myservo.write(pos);
  digitalWrite(BUTTON, LOW);
  pixels.clear();
  pixels.setBrightness(150);
  posLight = map(range, 0, 180, NUMPIXELS, 0);
  colorInput = map(analogRead(POT), 0, 1023, 0, 255);
  
  for(int i=0; i<posLight; i++) {
      pixels.setBrightness(colorInput);
      if (digitalRead(BUTTON) == LOW) {
        pixels.setPixelColor(i,pixels.Color(0,150,0));
        pixels.show();
      }
      else { 
        pixels.setPixelColor(i,pixels.Color(150,0,0));
        pixels.show();   
      }
  }
} 
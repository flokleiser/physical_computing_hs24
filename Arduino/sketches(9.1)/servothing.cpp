#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h>
#endif

#define SERVO 9
#define LED 10
#define POT A0

#define NUMPIXELS 9 

Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

Servo myservo;

int pos = 0;
int posLight = 0;
int colorInput = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    delay(1);
  }

  myservo.attach(SERVO);
  pinMode(POT, INPUT);
  pixels.begin(); 
  
  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");
}

void loop() {
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: "); Serial.println(range);
  }

  pos = map(range, 0, 180, 0, 180);

  myservo.write(pos);

  pixels.clear();
  pixels.setBrightness(50);

  posLight = map(range, 0, 180, 0, NUMPIXELS);
  colorInput = map(analogRead(POT), 0, 1023, 0, 255);
  
  for(int i=0; i<posLight; i++) {
      pixels.setPixelColor(i,pixels.Color(150,colorInput,-colorInput));
      pixels.show();   
  }
}
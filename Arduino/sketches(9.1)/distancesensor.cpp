#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();

Servo myservo;

#define POT A0
#define PIN 9

int pos = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) {                                                            
    delay(1);
  }

  myservo.attach(PIN);
  
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

  pos = map(analogRead(range), 0, 1023, 180, 0);
  myservo.write(pos);
}
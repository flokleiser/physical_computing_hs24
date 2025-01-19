#include <Arduino.h>

int brightness = 0;
int fadeSpeed = 3;

void setup() {
  pinMode(11, OUTPUT);
}

void loop() {
  analogWrite(11, brightness);
  brightness = brightness + fadeSpeed;

  if (brightness <= 0 || brightness >= 255) {
    fadeSpeed = -fadeSpeed;
  }

  delay(10);
}
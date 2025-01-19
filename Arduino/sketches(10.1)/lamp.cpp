#include <Arduino.h>
#define LAMP 9

int brightness = 0;
int fadeSpeed = 3;

void setup() {
  pinMode(LAMP, OUTPUT);
}

void loop() {
  analogWrite(LAMP, brightness);
  brightness = brightness + fadeSpeed;

  if (brightness <= 0 || brightness >= 255) {
    fadeSpeed = -fadeSpeed;
  }

  delay(10);
}
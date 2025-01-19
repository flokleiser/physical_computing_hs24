#include <Arduino.h>

#define MOTOR 9
#define POT A0

int speed = 0;

void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
  speed = map(analogRead(POT), 0, 1023, 0, 255);
  analogWrite(MOTOR, speed);
}
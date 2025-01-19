#include <Arduino.h>

void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(11));
}
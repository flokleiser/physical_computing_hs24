#include <Arduino.h>
#define POT A0
#define SERVO 11


void setup() {
  pinMode(POT, INPUT);
  pinMode(SERVO, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(POT);
  int angle = map(potValue, 0, 1023, 0, 180);
  analogWrite(SERVO, angle);
  Serial.println(angle);
  delay(15);
}
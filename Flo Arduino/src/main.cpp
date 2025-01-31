#include <Arduino.h>

#define POT A0
#define MOTOR 9


void setup() {
  pinMode(POT, INPUT);
  pinMode(MOTOR, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int potValue = analogRead(POT);
  int angle = map(potValue, 0, 1023, 0, 180);
  analogWrite(MOTOR, angle);

  Serial.println(angle);
  delay(15);

}
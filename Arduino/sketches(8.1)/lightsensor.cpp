#include <Arduino.h>

#define SENSOR A0
#define LAMP 11
#define THRESHOLD 700 

void setup() {
  pinMode(LAMP, OUTPUT);
  pinMode(SENSOR, INPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));

//this works but is dumb
  if (analogRead(A0) > THRESHOLD) {
    digitalWrite(LAMP, HIGH);
  } else {
    digitalWrite(LAMP, LOW);
  }
}
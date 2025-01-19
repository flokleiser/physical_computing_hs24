#include <Arduino.h>

#define INPUT_PIN 11 
#define LAMP 7

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(LAMP, OUTPUT);

  Serial.begin(9600);
}

void loop() {
    if (digitalRead(INPUT_PIN) == HIGH) {
        digitalWrite(LAMP, HIGH);
    } else {
        digitalWrite(LAMP, LOW);
    }
}
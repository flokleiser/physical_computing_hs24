#include <Arduino.h>
#define POT A0

int potValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(POT, INPUT);
}

void loop() {
    potValue = analogRead(POT);
    Serial.println(potValue);
    delay(100);
}


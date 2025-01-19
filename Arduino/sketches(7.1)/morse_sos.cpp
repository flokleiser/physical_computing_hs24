#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    S();
    O();
    S();
    delay(5000);                                                  
}

int dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);  
}

int dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);  
}

int S() {
  dot();
  dot();
  dot();
}

int O() {
  dash();
  dash();
  dash();
}
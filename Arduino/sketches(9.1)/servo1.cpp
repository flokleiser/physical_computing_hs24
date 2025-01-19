#include <Arduino.h>
#include <Servo.h>

Servo myservo;

#define POT A0
#define PIN 9

int pos = 0;
int POTINPUT = 0;

void setup() {
  myservo.attach(PIN);
  pinMode(POT, INPUT);
}

void loop() {
  pos = map(analogRead(POT), 0, 1023, 180, 0);

  myservo.write(pos);
}


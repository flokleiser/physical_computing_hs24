#include <Arduino.h>

#define SENSOR A0
#define LAMP 11
#define THRESHOLD 700 

int fadeSpeed = 3;
int sensorValue = 0;

void setup() {
  pinMode(LAMP, OUTPUT);
  pinMode(SENSOR, INPUT);

  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(SENSOR);
  int brightness = constrain(map(sensorValue, 850, 1000, 0, 255),0 , 255);

  analogWrite(LAMP, constrain(brightness, 0, 255));

  Serial.print(">sensorValue:");
  Serial.println(sensorValue);
  Serial.print(">brightness:");
  Serial.println(brightness);

  // Serial.println((String)"Sensor: " + sensorValue + " Brightness: " + brightness);

  delay(10);

}
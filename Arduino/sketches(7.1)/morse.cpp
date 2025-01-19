#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //S
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

  delay(1000);   

  //O         
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(400);  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(400);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);


  delay(1000); 

  //S
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

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
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6 
#define POT A0

#define NUMPIXELS 9 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(POT, INPUT);

  pixels.begin(); 
  Serial.begin(9600);
}

void loop() {
  pixels.clear();
  // pixels.setBrightness(50);

  int VALINPUT = map(analogRead(INPUT), 0, 1023, 0, 255);
  Serial.println((String)"VALINPUT: " + VALINPUT);
  
  for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i,pixels.Color(VALINPUT,255,255-VALINPUT));
      // pixels.setPixelColor(i,pixels.Color(40,40,40));
      pixels.setBrightness(VALINPUT);
      pixels.show();   
    }
}
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h>
#endif

#define PIN 6 
#define POT A0

// #define NUMPIXELS 9 
#define NUMPIXELS 9 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pinMode(POT, INPUT);
  pixels.begin(); 

  Serial.begin(9600);
}

void loop() {
  pixels.clear();
  pixels.setBrightness(5);

  int VALINPUT = map(analogRead(INPUT), 0, 1023, 0, NUMPIXELS);
  Serial.println((String)"VALINPUT: " + VALINPUT);
  
  for(int i=0; i<VALINPUT; i++) {
      pixels.setPixelColor(i,pixels.Color(150,0,0));
      pixels.show();   
    }
  if (VALINPUT > 7) {
    pixels.setPixelColor(8,pixels.Color(0,150,0));
  }


}


  // for(int i=0; i<VALINPUT; i++) {
  //   if (VALINPUT == 0) {
  //     // pixels.setPixelColor(i,pixels.Color(150,0,0));
  //     pixels.clear();
  //     pixels.setPixelColor(i,pixels.Color(150,0,0));
  //     pixels.show();
  //   }
  //   else {
  //     pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  //     pixels.show();   

  //   }
  // }
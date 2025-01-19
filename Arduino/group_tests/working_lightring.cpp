#include <Adafruit_NeoPixel.h>

#define NUMPIXELS    16
#define switchPin    3
#define NEOPIXEL_PIN 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  pinMode(switchPin, INPUT);
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
    setColor();
    for (int i = 0; i < NUMPIXELS; i++) {
      // pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    }
    pixels.show();
    delay(delayval);
}


void setColor(){
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}
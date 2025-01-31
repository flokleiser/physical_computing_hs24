#include <Arduino.h>
#include <LiquidCrystal.h>

#define POT A0
// #define SERVO 11
#define LCD_CONTRAST 9

int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  pinMode(POT, INPUT);
  // pinMode(SERVO, OUTPUT);
  pinMode(LCD_CONTRAST, OUTPUT);
  Serial.begin(9600);

  analogWrite(LCD_CONTRAST, 0);

  lcd.begin(16,2);
  lcd.clear();

}

void loop() {
  int potValue = analogRead(POT);
  int angle = map(potValue, 0, 1023, 0, 180);
  // analogWrite(SERVO, angle);

  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print(angle);

  Serial.println(angle);
  delay(15);

}
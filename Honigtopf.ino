#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float tempOffset = 2;
float targetTemp = 40;
float isTemp = 99.9;

void setup() {
  lcd.begin(16, 2);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  permDisplay();
}

void loop() {
  tempAdjust();
  tempDisplay(); 
}

void permDisplay() {
  lcd.print("Soll T   Ist T");
  lcd.setCursor(5, 1);
  lcd.print((char)223);
  lcd.setCursor(6, 1);
  lcd.print("C");
  lcd.setCursor(14, 1);
  lcd.print((char)223);
  lcd.setCursor(15, 1);
  lcd.print("C");
}

void tempDisplay() {
  lcd.setCursor(1, 1);
  lcd.print(targetTemp, 1);
  lcd.setCursor(10, 1);
  lcd.print(isTemp, 1);
}

void tempAdjust() {
  int buttonUp = digitalRead(6);
  int buttonDown = digitalRead(7);

  if (buttonUp == 0) {
    targetTemp += 0.5;
    delay(250);
    }
  if (buttonDown == 0) {
    targetTemp -= 0.5;
    delay(250);
  }
}


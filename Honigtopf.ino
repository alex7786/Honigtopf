#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

/*#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 
float currentTemp = 0;*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float tempOffset = 2;
float targetTemp = 40;
float isTemp = 99.9;

void setup() {
  lcd.begin(16, 2);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  permDisplay();
  //sensors.begin();  
}

void loop() {
  tempAdjust();
  tempDisplay(); 
  //readTemp();
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
    delay(200);
    }
  if (buttonDown == 0) {
    targetTemp -= 0.5;
    delay(200);
  }
}

void readTemp() {
  sensors.requestTemperatures();
  currentTemp= sensors.getTempCByIndex(0); // 0 refers to the first IC on the wire 
  delay(100);
}


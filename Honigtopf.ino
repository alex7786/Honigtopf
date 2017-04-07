#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

//PINS
#define ONE_WIRE_BUS 9  //CHECK PIN!!!

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pinButtonUp = 6;
int pinButtonDown = 7;
int pinSSR = 8;        //CHECK PIN!!!

//VARIABLES
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 
float currentTemp = 0;
float tempOffset = 2;
float targetTemp = 40;
float isTemp = 99.9;

void setup() {
  lcd.begin(16, 2);
  pinMode(pinButtonUp, INPUT_PULLUP);
  pinMode(pinButtonDown, INPUT_PULLUP);
  pinMode(pinSSR, OUTPUT);
  permDisplay();
  sensors.begin();  
}

void loop() {
  tempAdjust();
  tempDisplay(); 
  //readTemp();
  //tempControl();
}

void permDisplay() {                //permanent display elements
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

void tempDisplay() {                //changing display elements
  lcd.setCursor(1, 1);
  lcd.print(targetTemp, 1);
  lcd.setCursor(10, 1);
  lcd.print(isTemp, 1);
}

void tempAdjust() {                //adjusting of the target temperature
  int buttonUp = digitalRead(pinButtonUp);
  int buttonDown = digitalRead(pinButtonDown);

  if (buttonUp == 0) {
    targetTemp += 0.5;
    delay(200);
    }
  if (buttonDown == 0) {
    targetTemp -= 0.5;
    delay(200);
  }
}

void readTemp() {                //readout of the DS18B20 sensor
  sensors.requestTemperatures();
  currentTemp= sensors.getTempCByIndex(0); // 0 refers to the first IC on the wire 
  delay(100);
}

void tempControl() {                //controlling the SSR with an +- tempOffset big hysteresis
  if (digitalRead(pinSSR) == false && currentTemp <= (targetTemp - tempOffset)){
    digitalWrite(pinSSR, HIGH);
  }
  else if (digitalRead(pinSSR) == true && currentTemp >= (targetTemp + tempOffset)){
    digitalWrite(pinSSR, LOW);
  }
}


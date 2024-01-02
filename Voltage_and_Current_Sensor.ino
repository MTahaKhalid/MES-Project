#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);
const int sensorIn = A0;
int mVperAmp = 185; // 5A version SC712 – use 100 for 20A Module or 66 for 30A Module
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;

int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Voltage :");
  lcd.setCursor(0, 1);
  lcd.print("Amps :");
}

void loop() {
  int value = analogRead(sensorIn);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2 / (R1 + R2));

  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  Watt = (AmpsRMS * 240 / 1.2);

  lcd.setCursor(9, 0);
  lcd.print(vIN, 2);
  lcd.print("v ");

  lcd.setCursor(7, 1);
  lcd.print(AmpsRMS, 2);
  lcd.print("A ");
  
  Serial.print("Voltage: ");
  Serial.print(vIN);
  Serial.print("v, Amps: ");
  Serial.print(AmpsRMS);
  Serial.println("A");

  delay(1000);
}

float getVPP() {
  float result;
  int readValue;
  int maxValue = 0;
  int minValue = 1024;

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) {
    readValue = analogRead(sensorIn);
    if (readValue > maxValue) {
      maxValue = readValue;
    }
    if (readValue < minValue) {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * 5.0) / 1024.0;
  return result;
}

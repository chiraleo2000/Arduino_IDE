#include <M5Stack.h>
//PINs Setting
const int ana_LDR = 35; // LDR Analog
const int digit_LDR = 5; // LDR Digital

void setup() {
  M5.begin();
  pinMode(digit_LDR, INPUT_PULLUP);
  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.printf("Luminosity");
  dacWrite(25, 0);
}
void loop() {
  uint16_t luminosity = analogRead(ana_LDR);
  uint16_t d_data = digitalRead(digit_LDR);
  Serial.printf(" Analog: %0d digital: %0d   \n", luminosity, d_data);
  M5.Lcd.setCursor(40, 40, 4);
  M5.Lcd.printf(" Analog: %0d digital: %0d   \n", luminosity, d_data);
  delay(200);
}

#include <M5Stack.h>
void setup() {
  // initialization
  M5.begin(true, false, true);
  pinMode(2, INPUT_PULLUP);
  dacWrite(25, 0);//disable the speak noise
  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.printf("JOYSTICK");
}
void loop() {
  uint16_t x_data = analogRead(35);
  uint16_t y_data = analogRead(36);
  uint8_t button_data = digitalRead(2);
  M5.Lcd.setCursor(30, 120, 4);
  M5.Lcd.printf("x:%04d y:%04d button:%d \n", x_data, y_data, button_data);
  delay(200);
}

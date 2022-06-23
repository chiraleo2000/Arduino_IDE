#include <M5Stack.h>

void setup() {
  M5.begin(true, false, true);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("DC motor example");
  M5.Lcd.setCursor(30, 210);
  M5.Lcd.printf("Forward");
  M5.Lcd.setCursor(140, 210);
  M5.Lcd.println("Stop");
  M5.Lcd.setCursor(220, 210);
  M5.Lcd.println("Reverse");
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
}
void loop() {
  M5.update();
  if (M5.BtnA.wasReleased())
  {
    digitalWrite(16, HIGH);
    digitalWrite(17, LOW);
  }
  else if (M5.BtnB.wasReleased())
  {
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
  }
  else if (M5.BtnC.wasReleased())
  {
    digitalWrite(16, LOW);
    digitalWrite(17, HIGH);
  }
}

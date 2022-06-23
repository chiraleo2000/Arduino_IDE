#include <M5Stack.h>
int t1;
int t2;
int t3;
void setup() {
  M5.begin();
  M5.Lcd.setBrightness(128);
  M5.Lcd.setTextSize(2.5);
  t1 = 0;
  t2 = 0;
  t3 = 0;
  M5.Lcd.setTextColor(BLUE, WHITE);
  M5.Speaker.setBeep(4800, 100);
}
void loop() {
  M5.Lcd.setCursor(0, 0);
  if (M5.BtnA.read() == 1) {
    t1 = t1 + M5.BtnA.read();
    M5.Lcd.setTextColor(RED, GREEN);
    M5.Speaker.tone(762, 100);
    delay(200);
  }
  else if (M5.BtnB.read() == 1) {
    t2 = t2 + M5.BtnB.read();
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Speaker.tone(485, 100);
    delay(200);
  }
  else if (M5.BtnC.read() == 1) {
    t3 = t3 + M5.BtnC.read();
    M5.Lcd.setTextColor(CYAN, PINK);
    M5.Speaker.tone(980, 100);
    delay(200);
  }
  M5.Lcd.printf("Read BtnA = %d \r\n", t1);
  M5.Lcd.printf("Read BtnB = %d \r\n", t2);
  M5.Lcd.printf("Read BtnC = %d \r\n", t3);
  delay(100);
  M5.update();
}

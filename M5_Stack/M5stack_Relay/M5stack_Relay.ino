#include <M5Stack.h>
int t1;
int t2;
void setup() {
  M5.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setTextColor(YELLOW, BLACK);
  //disable the speak noise
  dacWrite(25, 0);
  pinMode(16, OUTPUT);// RELAY Pin setting
  pinMode(17, OUTPUT);// RELAY Pin setting
  t1 = 0;
  t2 = 0;
}

void loop() {
  t1 = M5.BtnA.read() + t1;
  t2 = M5.BtnB.read() + t2;
  if ( t1 % 2 == 1) {
    digitalWrite(16, HIGH);// RELAY1 Unit work
    delay(100);
  }
  else if ( t1 % 2 == 0) {
    digitalWrite(16, LOW);// RELAY1 Unit work
    delay(100);
  }
  if ( t2 % 2 == 1) {
    digitalWrite(17, HIGH);// RELAY2 Unit work
    delay(100);
  }
  else if ( t2 % 2 == 0) {
    digitalWrite(17, LOW);// RELAY1 Unit work
    delay(100);
  }
}

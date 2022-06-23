#include <M5Stack.h>
const int phaseA = 2;
const int phaseB = 5;

#define GET_CODE() uint8_t(digitalRead(phaseA)<<4 | digitalRead(phaseB))
int32_t count_change = 0;
uint8_t code = 0;
uint8_t code_old = 0;
void encoderEvent()
{
  code = GET_CODE();
  if (code != code_old)
  {
    if (code == 0x00)
    {
      if (code_old == 0x10)
      {
        count_change--;
      }
      else
      {
        count_change++;
      }
    }
    code_old = code;
  }
}
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  pinMode(phaseA, INPUT_PULLUP);
  pinMode(phaseB, INPUT_PULLUP);
  dacWrite(25, 0);
  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("ENCODER");
  code = GET_CODE();
  code_old = code;
}

void loop() {
  encoderEvent();
  M5.Lcd.setCursor(30, 120, 4);
  M5.Lcd.printf("code = %05d", count_change);
  delay(1);
}

#include <M5Stack.h>
const int MOTOR_A = 2;
const int MOTOR_B = 5;
const int MOTOR_C = 16;
const int MOTOR_D = 17;
const int pinMotor[2][4] = {{MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D}, {MOTOR_D, MOTOR_C, MOTOR_B, MOTOR_A}};
const byte logic_fullstep[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {1, 0, 0, 1}};
const byte logic_wave[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
const byte logic_halfstep[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};
int count;
void setup() {
  M5.begin(true, false, true);
  M5.Lcd.setBrightness(128);
  M5.Lcd.setTextSize(2);
  pinMode(pinMotor[0][0], OUTPUT);
  pinMode(pinMotor[0][1], OUTPUT);
  pinMode(pinMotor[0][2], OUTPUT);
  pinMode(pinMotor[0][3], OUTPUT);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(40, 100);
  M5.Lcd.println(" Start Stepper Motor  ");
  delay(2000);
  M5.Lcd.clear(BLACK);
}
void loop() {
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("         Wave Drive        ");
  //Wave Drive
  for (int i = 0; i < 2048; i++) //360 degree clockwise
  {
    wave(0);
    delay(2);
  }
  delay(10);
  for (int i = 0; i < 2048; i++) //360 degree counter-clockwise
  {
    wave(1);
    delay(2);
  }
  delay(2000);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("      Full Step Drive      ");
  //Full Step Drive
  for (int i = 0; i < 2048; i++) //360 degree clockwise
  {
    fullstep(0);
    delay(2);
  }
  delay(10);
  for (int i = 0; i < 2048; i++) //360 degree counter-clockwise
  {
    fullstep(1);
    delay(2);
  }
  delay(2000);
  //Half Step Drive
    M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("      Half Step Drive      ");
  for (int i = 0; i < 2048; i++) //360 degree clockwise
  {
    halfstep(0);
    delay(2);
  }
  delay(10);
  for (int i = 0; i < 4096; i++) //360 degree counter-clockwise
  {
    halfstep(1);
    delay(2);
  }
  delay(2000);
}
void fullstep(int direct) {
  count++;
  int step = count % 4;
  digitalWrite(pinMotor[direct][0], logic_fullstep[step][0]);
  digitalWrite(pinMotor[direct][1], logic_fullstep[step][1]);
  digitalWrite(pinMotor[direct][2], logic_fullstep[step][2]);
  digitalWrite(pinMotor[direct][3], logic_fullstep[step][3]);
  delay(2);
}

void wave(int direct) {
  count++;
  int step = count % 4;
  digitalWrite(pinMotor[direct][0], logic_wave[step][0]);
  digitalWrite(pinMotor[direct][1], logic_wave[step][1]);
  digitalWrite(pinMotor[direct][2], logic_wave[step][2]);
  digitalWrite(pinMotor[direct][3], logic_wave[step][3]);
  delay(2);
}

void halfstep(int direct) {
  count++;
  int step = count % 8;
  digitalWrite(pinMotor[direct][0], logic_halfstep[step][0]);
  digitalWrite(pinMotor[direct][1], logic_halfstep[step][1]);
  digitalWrite(pinMotor[direct][2], logic_halfstep[step][2]);
  digitalWrite(pinMotor[direct][3], logic_halfstep[step][3]);
  delay(2);
}

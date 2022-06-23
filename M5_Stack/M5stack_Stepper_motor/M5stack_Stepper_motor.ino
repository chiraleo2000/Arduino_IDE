#include <M5Stack.h>
const int MOTOR_A_A = 2;
const int MOTOR_A_B = 5;
const int MOTOR_A_C = 16;
const int MOTOR_A_D = 17;
void setup() {
  M5.begin();
  pinMode(MOTOR_A_A, OUTPUT);
  pinMode(MOTOR_A_B, OUTPUT);
  pinMode(MOTOR_A_C, OUTPUT);
  pinMode(MOTOR_A_D, OUTPUT);
}
void loop() {
  digitalWrite(MOTOR_A_A, HIGH);
  digitalWrite(MOTOR_A_B, HIGH);
  digitalWrite(MOTOR_A_C, LOW);
  digitalWrite(MOTOR_A_D, LOW);
  delay(2);
  digitalWrite(MOTOR_A_A, LOW);
  digitalWrite(MOTOR_A_B, HIGH);
  digitalWrite(MOTOR_A_C, HIGH);
  digitalWrite(MOTOR_A_D, LOW);
  delay(2);
  digitalWrite(MOTOR_A_A, LOW);
  digitalWrite(MOTOR_A_B, LOW);
  digitalWrite(MOTOR_A_C, HIGH);
  digitalWrite(MOTOR_A_D, HIGH);
  delay(2);
  digitalWrite(MOTOR_A_A, HIGH);
  digitalWrite(MOTOR_A_B, LOW);
  digitalWrite(MOTOR_A_C, LOW);
  digitalWrite(MOTOR_A_D, HIGH);
  delay(2);
}

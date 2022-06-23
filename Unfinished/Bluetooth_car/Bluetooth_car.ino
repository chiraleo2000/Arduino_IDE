/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino with HC-06/HC-05
  Bluetooth 2.0 Serial Port Profile (SPP) module
  to connect your project to Blynk.

  Note: This only works on Android! iOS does not support SPP :(
        You may need to pair the module with your smartphone
        via Bluetooth settings. Default pairing password is 1234

  Feel free to apply it to any other example. It's simple!

  NOTE: Bluetooth support is in beta!

  You can receive x and y coords for joystick movement within App.

  App project setup:
    Two Axis Joystick on V1 in MERGE output mode.
    MERGE mode means device will receive both x and y within 1 message
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT
// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "car";
const int RightMotorF = 3;
const int RightMotorB = 4;
const int LeftMotorF = 5;
const int LeftMotorB = 6;
float LMotor_offset, RMotor_offset;
float Turn_Speed = 0, Turn_Speed_K = 0;
float Run_Speed = 0, Run_Speed_K = 0, Run_Speed_T = 0;
float LOutput = 0; float ROutput = 0;
int x, y;
void setup()
{
  pinMode(RightMotorF, OUTPUT);
  pinMode(RightMotorB, OUTPUT);
  pinMode(LeftMotorF, OUTPUT);
  pinMode(LeftMotorB, OUTPUT);
  x = 0;
  y = 0;
  LOutput = 0;
  ROutput = 0;
  // Debug console
  DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");
  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}
void XY_TO_RUN_TURN_SPEEDS() {
  if (x != 128) {
    Turn_Speed = map(x, 0, 255, 160, -160);
  } else {
    Turn_Speed = 0;
  }
  if (y != 128) {
    Run_Speed = map(y, 0, 255, -300, 300);
  } else {
    Run_Speed = 0;
  }
  LOutput = Run_Speed + Turn_Speed;
  ROutput = Run_Speed - Turn_Speed;
  LOutput = -LOutput;
}
void loop()
{
  Blynk.run(); // To Run Blynk
  XY_TO_RUN_TURN_SPEEDS(); //X of the Joystick represent the turn speed and Y the RUN speed
}

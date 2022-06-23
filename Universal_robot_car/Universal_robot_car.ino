//Define the Pins
//switch automatic/manual
int switch_auto = 22;
int switch_manual = 25;
int LED_auto = 24;
int LED_manual = 26;
//Motor 1
int pinAIN1 = 11; //Direction
int pinAIN2 = 12; //Direction
int pinPWMA = 13; //Speed

//Motor 2
int pinBIN1 = 10; //Direction
int pinBIN2 = 9; //Direction
int pinPWMB = 8; //Speed

//Standby
int pinSTBY = 7;

//Constants to help remember the parameters
static boolean turnCW = 0;  //for motorDrive function
static boolean turnCCW = 1; //for motorDrive function
static boolean motor1 = 0;  //for motorDrive, motorStop, motorBrake functions
static boolean motor2 = 1;  //for motorDrive, motorStop, motorBrake functions

// joystrick
int joyPin_X = A0;                 // slider variable connecetd to analog pin 0
int joyPin_Y = A1;                 // slider variable connecetd to analog pin 1

int x;
int y;
// IR-4-sensors-boards
int IR_Sensor_1 = 6;
int IR_Sensor_2 = 5;
int IR_Sensor_3 = 4;
int IR_Sensor_4 = 3;
//KY-32-avoid-IR-sensor
int KY32_sensor = 22;

void motorDrive(boolean motorNumber, boolean motorDirection, int motorSpeed)
{
  /*
    This Drives a specified motor, in a specific direction, at a specified speed:
    - motorNumber: motor1 or motor2 ---> Motor 1 or Motor 2
    - motorDirection: turnCW or turnCCW ---> clockwise or counter-clockwise
    - motorSpeed: 0 to 255 ---> 0 = stop / 255 = fast
  */
  boolean pinIn1;  //Relates to AIN1 or BIN1 (depending on the motor number specified)
  //Specify the Direction to turn the motor
  //Clockwise: AIN1/BIN1 = HIGH and AIN2/BIN2 = LOW
  //Counter-Clockwise: AIN1/BIN1 = LOW and AIN2/BIN2 = HIGH
  if (motorDirection == turnCW)
    pinIn1 = HIGH;
  else
    pinIn1 = LOW;

  //Select the motor to turn, and set the direction and the speed
  if (motorNumber == motor1)
  {
    digitalWrite(pinAIN1, pinIn1);
    digitalWrite(pinAIN2, !pinIn1);  //This is the opposite of the AIN1
    analogWrite(pinPWMA, motorSpeed);
  }
  else
  {
    digitalWrite(pinBIN1, pinIn1);
    digitalWrite(pinBIN2, !pinIn1);  //This is the opposite of the BIN1
    analogWrite(pinPWMB, motorSpeed);
  }
  //Finally , make sure STBY is disabled - pull it HIGH
  digitalWrite(pinSTBY, HIGH);
}
void motorBrake(boolean motorNumber)
{
  if (motorNumber == motor1)
    analogWrite(pinPWMA, 0);
  else
    analogWrite(pinPWMB, 0);
}
void motorStop(boolean motorNumber)
{
  if (motorNumber == motor1) {
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, LOW);
  }
  else
  {
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, LOW);
  }
}
void motorsStandby()
{
  digitalWrite(pinSTBY, LOW);
}
void automatic_mode()
{
  bool obstacle = digitalRead (KY32_sensor);
  digitalWrite(LED_manual, LOW);
  digitalWrite(LED_auto, HIGH);
  Serial.println("automatic_mode");
  if (obstacle == HIGH) // If a signal is detected, the LED will light up when something coming.
  {
    Serial.println("No obstacle");
  }
  else if (obstacle == LOW)
  {
    Serial.println("Obstacle detected");
    motorDrive( motor1 , turnCCW, 200);
    motorDrive( motor2 , turnCCW, 200);
    delay(1000);
    motorDrive( motor1 , turnCCW, 200);
    motorStop( motor2);
    delay(1000);
  }
  int statusSensor1 = digitalRead (IR_Sensor_1);
  int statusSensor2 = digitalRead (IR_Sensor_2);
  int statusSensor3 = digitalRead (IR_Sensor_3);
  int statusSensor4 = digitalRead (IR_Sensor_4);
  if (statusSensor1 == 0) {
    motorDrive( motor2 , turnCW, 100);
    motorStop( motor1);
    delay(500);
  }
  else if (statusSensor2 == 0) {
    motorDrive( motor1 , turnCW, 100);
    motorStop( motor2);
    delay(500);
  }
  else if (statusSensor3 == 0) {
    motorDrive( motor1 , turnCW, 100);
    motorStop( motor2);
    delay(500);
  }
  else if (statusSensor1 == 1 && statusSensor2 == 1) {
    motorDrive( motor1 , turnCW, 125);
    motorDrive( motor2 , turnCW, 125);
    delay(50);
  }
}
void manual_mode()
{
  int x = analogRead(joyPin_X);
  int y = analogRead(joyPin_Y);
  digitalWrite(LED_manual, HIGH);
  digitalWrite(LED_auto, LOW);
  Serial.println("manual_mode");
  if ( x < 300 ) {
    motorDrive( motor1 , turnCCW, 200);
    motorDrive( motor2 , turnCCW, 200);
  }
  else if (x < 800) {
    motorStop( motor1);
    motorStop( motor2);
  }
  else if (x >= 800) {
    motorDrive( motor1 , turnCW, 200);
    motorDrive( motor2 , turnCW, 200);
  }
  if (y < 300) {
    motorDrive( motor1 , turnCW, 200);
    motorStop( motor2);
  }
  else if (y > 800) {
    motorDrive( motor2 , turnCW, 200);
    motorStop( motor1);
  }
}
void setup()
{
  //Set the PIN Modes
  pinMode(joyPin_X, INPUT);
  pinMode(joyPin_Y, INPUT);
  pinMode (IR_Sensor_1, INPUT);
  pinMode (IR_Sensor_2, INPUT);
  pinMode (IR_Sensor_3, INPUT);
  pinMode (IR_Sensor_4, INPUT);
  pinMode (KY32_sensor, INPUT);
  pinMode(switch_auto, INPUT);

  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinSTBY, OUTPUT);
  pinMode(LED_auto, OUTPUT);
  pinMode(LED_manual, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int m1 = digitalRead(switch_auto);
  int m2 = digitalRead(switch_manual);
  Serial.println(m1);
  if (m2 == 1 && m1 == 0) {
    manual_mode();
  }
  else if (m1 == 1 && m2 == 0) {
    automatic_mode();
  }
}

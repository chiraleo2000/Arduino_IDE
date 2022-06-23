#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
int potpin1= 0;
int potpin2= 1;
int potpin3= 2;
int potpin4= 3;
int potpin5= 4;
int potpin6= 5;
int angle1;
int angle2;
int angle3;
int angle4;
int angle5;
int angle6;
int val1;
int val2;
int val3;
int val4;
int val5;
int val6;
void setup() {
  // put your setup code here, to run once:
  pinMode(potpin1, INPUT);
  pinMode(potpin2, INPUT);
  pinMode(potpin3, INPUT); 
  pinMode(potpin4, INPUT);
  pinMode(potpin5, INPUT);
  pinMode(potpin6, INPUT);
myservo1.attach(3);
myservo2.attach(9);
myservo3.attach(5);
myservo4.attach(6);
myservo5.attach(7);
myservo6.attach(8);
Serial.begin(9600); // Starts the serial communication
delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
val1 = analogRead(potpin1);
val2 = analogRead(potpin2);
val3 = analogRead(potpin3);
val4 = analogRead(potpin4);
val5 = analogRead(potpin5);
val6 = analogRead(potpin6);
angle1 = ((((((val1/11)*9)/31)*10)/3)*2);
angle2 = ((((((val2/11)*9)/31)*10)/3)*2);
angle3 = ((((((val3/11)*9)/31)*10)/3)*2);
angle4 = ((((((val4/11)*9)/31)*10)/3)*2);
angle5 = ((((((val5/11)*9)/31)*10)/3)*2);
angle6 = ((((((val6/11)*9)/31)*10)/3)*2);
delay(50);
myservo1.write(angle1);
myservo2.write(angle2);
myservo3.write(angle3);
myservo4.write(angle4);
myservo5.write(angle5);
myservo6.write(angle6);
delay(50);
Serial.print(angle1);
Serial.print("  ");
Serial.print(angle2);
Serial.print("  ");
Serial.print(angle3);
Serial.print("  ");
Serial.print(angle4);
Serial.print("  ");
Serial.print(angle5);
Serial.print("  ");
Serial.println(angle6);
delay(50);
}

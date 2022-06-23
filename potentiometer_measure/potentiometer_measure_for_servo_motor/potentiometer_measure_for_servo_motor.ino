#include <Servo.h>
Servo myservo1;
int potpin= 0;
int val = 0;
float angle = 0;
void setup() {
  // put your setup code here, to run once:
myservo1.attach(3);
myservo1.write(0);
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(potpin);
angle = ((((((val/11)*9)/31)*10)/3)*2);
myservo1.write(angle);
Serial.print(val);
Serial.print("  ");
Serial.println(angle);
}

#include <Servo.h>
Servo myservo1;
int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
int value1 = 0;                  // variable to read the value from the analog pin 0
int value2 = 0;                // variable to read the value from the analog pin 1
int angle = 0;
void setup() {
  // put your setup code here, to run once:
  myservo1.attach(3);
  Serial.begin(9600);
}
int treatValue(int data) {
  return (data);
 }
void loop() {
  // put your main code here, to run repeatedly:
  value1 = analogRead(joyPin1);
  value2 = analogRead(joyPin2);
  if(value2<=600&&value2>=251){
    myservo1.write(90);
    }
  else if(value2<=900&&value2>=601){
    myservo1.write(135);
    }
  else if(value2>900){
    myservo1.write(180);
    }
  else if(value2<=250&&value2>=51){
    myservo1.write(45);
    }
  else{
    myservo1.write(0);
    }
  Serial.print(treatValue(value1));
  Serial.print("  ");
  Serial.println(treatValue(value2));
  delay(10);
}

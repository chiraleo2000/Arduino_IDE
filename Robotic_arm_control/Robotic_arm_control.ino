#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;
Servo myservo10;
Servo myservo11;
Servo myservo12;

int angle1;
int angle2;
int angle3;
int angle4;
int angle5;
int angle6;
int angle7;
int angle8;
int angle9;
int angle10;
int angle11;
int angle12;

void setup() {
  // put your setup code here, to run once:
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);
  myservo7.attach(8);
  myservo8.attach(9);
  myservo9.attach(10);
  myservo10.attach(11);
  myservo11.attach(12);
  myservo12.attach(13);
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  myservo5.write(90);
  myservo6.write(90);
  myservo7.write(90);
  myservo8.write(90);
  myservo9.write(90);
  myservo10.write(90);
  myservo11.write(90);
  myservo12.write(90);
  Serial.begin(9600);
  delay(2000);
}

void forward(){

delay(10);
}

void backward(){
  
delay(10);
}

void right_turn(){
  
delay(10);
}

void left_turn(){
  
delay(10);
}

void right_move(){
  
delay(10);
}
void left_move(){

delay(10);
}
void loop(){
  forward()
  backward()
  delay(10);
}

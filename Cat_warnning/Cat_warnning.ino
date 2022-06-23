int IRSensor1 = 2; // connect ir sensor to arduino pin 2
int IRSensor2 = 3; // connect ir sensor to arduino pin 3
int Red_LED = 4;
int Blue_LED1 = 5;
int Blue_LED2 = 6;
int buzzpin1 = 11;
int buzzpin2 = 12;
void setup(){
  pinMode(IRSensor1, INPUT);
  pinMode(IRSensor2, INPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Blue_LED1, OUTPUT);
  pinMode(Blue_LED2, OUTPUT);
  pinMode(buzzpin1, OUTPUT);
  pinMode(buzzpin2, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  int statusSensor1 = digitalRead(IRSensor1);
  int statusSensor2 = digitalRead(IRSensor2);
switch (statusSensor1) {
  case 0:
    digitalWrite(buzzpin1, HIGH);
    digitalWrite(Blue_LED1, HIGH);
    digitalWrite(Red_LED, LOW);
    break;
  case 1:
    digitalWrite(buzzpin1, LOW);    
    digitalWrite(Blue_LED1, LOW);
    digitalWrite(Red_LED, HIGH);
    break;
}
switch (statusSensor2) {
  case 0:
    digitalWrite(buzzpin2, HIGH);
    digitalWrite(Red_LED, LOW);
    digitalWrite(Blue_LED2, HIGH);
    break;
  case 1:
    digitalWrite(buzzpin2, LOW);
    digitalWrite(Red_LED, HIGH);
    digitalWrite(Blue_LED2, LOW);
    break;
}
delay(100);
    digitalWrite(Red_LED, LOW);
    Serial.print(statusSensor1);
    Serial.print("   ");
    Serial.println(statusSensor2);
delay(100);
}

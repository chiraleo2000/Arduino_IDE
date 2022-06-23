int IRSensor1 = 2; // connect ir sensor to arduino pin 2
int buzzpin = 12;
void setup() 
{
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  int statusSensor1 = digitalRead (IRSensor1);
  Serial.print(statusSensor1);
}

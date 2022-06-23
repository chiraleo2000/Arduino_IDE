int IR_avoid_Sensor_analog_read = A0;
int IR_avoid_Sensor_digital_read = 12;
void setup()
{
  pinMode (IR_avoid_Sensor_analog_read, INPUT);
  pinMode (IR_avoid_Sensor_digital_read, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  int Range_detection = analogRead (IR_avoid_Sensor_analog_read);
  int statusSensor = digitalRead (IR_avoid_Sensor_digital_read);
  if (statusSensor == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.print(statusSensor);
  // 1 == no detected
  //0 = detected
  Serial.print("   ");
  Serial.println(Range_detection);
  delay(100);

}

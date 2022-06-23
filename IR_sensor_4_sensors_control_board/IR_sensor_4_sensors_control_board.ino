int IR_Sensor_1 = 4;
int IR_Sensor_2 = 5;
int IR_Sensor_3 = 6;
int IR_Sensor_4 = 7;
void setup()
{
  pinMode (IR_Sensor_1, INPUT);
  pinMode (IR_Sensor_2, INPUT);
  pinMode (IR_Sensor_3, INPUT);
  pinMode (IR_Sensor_4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  int statusSensor1 = digitalRead (IR_Sensor_1);
  int statusSensor2 = digitalRead (IR_Sensor_2);
  int statusSensor3 = digitalRead (IR_Sensor_3);
  int statusSensor4 = digitalRead (IR_Sensor_4);
Serial.print(statusSensor1);
Serial.print("   ");
Serial.print(statusSensor2);
Serial.print("   ");
Serial.print(statusSensor3);
Serial.print("   ");
Serial.println(statusSensor4);
delay(100);
// 1 == no detected
//0 = detected
}

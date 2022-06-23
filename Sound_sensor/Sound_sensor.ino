int Sound_sensor_analog = A2; // connect sound sensor tp srduino pin 2
int Sound_sensor_digital = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(Sound_sensor_analog, INPUT);
  pinMode(Sound_sensor_digital, INPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int statussensor1 = analogRead (Sound_sensor_analog);
  int statussound = (((((statussensor1/11))*10)/31)*14)/3;
  int statussensor2 = digitalRead (Sound_sensor_digital);
  Serial.print(statussensor1);
  Serial.print("  ");
  Serial.print(statussound);
  Serial.print("  ");
  Serial.println(statussensor2);
  }

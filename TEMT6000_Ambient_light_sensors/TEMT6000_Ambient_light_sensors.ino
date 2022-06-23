int temt6000Pin = 13;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(temt6000Pin);
  Serial.println(value); 
  delay(200);
}

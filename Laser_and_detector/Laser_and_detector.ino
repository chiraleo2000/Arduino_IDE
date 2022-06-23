int laser = 6;
int detector = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(detector, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(laser, HIGH);
  boolean value = digitalRead(detector);
  Serial.println(value);
  delay(100);
}

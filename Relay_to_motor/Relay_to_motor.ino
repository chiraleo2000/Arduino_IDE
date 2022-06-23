int switchpin = 11;
int outpin = 12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchpin, INPUT);
  pinMode(outpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(switchpin);
  Serial.println(buttonState);{
      (buttonState == 1);
    {
    digitalWrite(outpin, HIGH);
    delay(5000);
    digitalWrite(outpin, LOW);
    }
    delay(10);
    }
}

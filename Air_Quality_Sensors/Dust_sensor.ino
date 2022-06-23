
int measurePin = A5; //Connect dust sensor to Arduino A5 pin
int ledPower = 12;   //Connect 3 led driver pins of dust sensor to Arduino D12
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int buzzing = 6;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzing, OUTPUT);
}

void loop() {
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5 / 1023.0);
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.172 * calcVoltage - 0.1;    //mg/m^3
  if (dustDensity <= 0.05) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(buzzing, LOW);
    delay(500);
  }
  else if (dustDensity <= 0.10) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(buzzing, LOW);
    delay(500);
    
  }
  else if (dustDensity <= 0.15) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(buzzing, LOW);
    delay(500);
  }
  else if (dustDensity <= 0.20) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(buzzing, LOW);
    delay(500);
  }
  else {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(buzzing, HIGH);
    delay(500);
  }
  Serial.print("Raw Signal Value (0-1023):");
  Serial.print(voMeasured);

  Serial.print("/Voltage: ");
  Serial.print(calcVoltage);

  Serial.print("/Dust Density: ");
  Serial.print(dustDensity); // unit: mg/m3
  Serial.println(" mg/m3");
  delay(500);
}

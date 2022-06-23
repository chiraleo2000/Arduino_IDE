#include <U8glib.h>
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
#define MQ135_PIN A0
int measurePin = A2;
int ledPower = 9;
int SENSOR_VALUE;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured;
float calcVoltage;
float dustDensity; 
int buzzing = 6;
float sensor_volt;
float RS_gas;
float ratio;
float co;
void setup() {
  Serial.begin(9600);
  pinMode(buzzing, OUTPUT);
  pinMode(ledPower, OUTPUT);
  digitalWrite(buzzing, LOW);
  delay(10000);
}

void loop() {
  SENSOR_VALUE = analogRead(MQ135_PIN);
  Serial.print("Air quality value: ");
  Serial.print(SENSOR_VALUE);
  Serial.println(" units");
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5 / 1023.0);
  dustDensity = 0.172 * calcVoltage - 0.1;    //mg/m^3
  Serial.print("Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" mg/m3");
  //-Replace the name "R0" with the value of R0 in the demo of First Test -/
  float RL = 10000;
  float Ro = 40000;
  float sensorValue = analogRead(A1);
  sensor_volt = (((float)sensorValu e * 5.0) / 1023);
  RS_gas = ((5.0 * RL * 0.001) / sensor_volt) - (RL * 0.001); // Depend on RL on yor module
  ratio = RS_gas / (Ro * 0.001); // ratio = RS/R0
  co = pow(ratio, -2.244);
  co = co * 599.65;
  if (SENSOR_VALUE >= 500) {
    digitalWrite(buzzing, HIGH);
  }
  else if (co >= 25) {
    digitalWrite(buzzing, HIGH);
  }
  else if (dustDensity >= 0.2) {
    digitalWrite(buzzing, HIGH);
  }
  else {
    digitalWrite(buzzing, LOW);
  }
  Serial.print("CO: ");
  Serial.print(co);
  Serial.println(" ppm");
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  delay(1500);
  digitalWrite(buzzing, LOW);
  delay(1500);
}
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 12);
  u8g.print("Air_quality: ");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(78, 12);
  u8g.print(SENSOR_VALUE);
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(95, 12);
  u8g.println(" unit");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 25);
  u8g.print("CO: ");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(30, 25);
  u8g.print(co);
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(55, 25);
  u8g.println(" ppm");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 38);
  u8g.print("PM 2.5: ");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(50, 38);
  u8g.print(dustDensity);
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(80, 38);
  u8g.println(" mg/m^3");
}

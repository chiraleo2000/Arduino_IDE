#include <SoftwareSerial.h>
#include "DHT.h"
#include <Wire.h>
#include <BH1750FVI.h>
#include <Adafruit_BMP085.h>
#define MQ135_PIN A0
#define DHTPIN A2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
int SENSOR_VALUE;
int buzzpin = 7;
int capteur_D = 8;
String str;
String warning;
Adafruit_BMP085 bmp;
SoftwareSerial espSerial(5, 6);
void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  Serial.println("DHTxx test!");
  pinMode(capteur_D, INPUT);
  pinMode(buzzpin, OUTPUT);
  dht.begin();
  LightSensor.begin();
  if (!bmp.begin())
  {
    Serial.println("BMP180 sensor not found");
    while (1) {}
  }
}
void loop() {
  uint16_t lux = LightSensor.GetLightIntensity();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hi = dht.computeHeatIndex(t, h);
  float dp = (t - (100 - h) / 5);   //  dewpoint calculation using Celsius value
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print((t + bmp.readTemperature()) / 2);
  Serial.print(" *C ");
  Serial.print("\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print("Dew point: ");
  Serial.print(dp);
  Serial.println(" *C");
  Serial.print("Air quality value (Dust): ");
  Serial.print(SENSOR_VALUE * 0.003);
  Serial.print(" mg/m^3 ");
  Serial.print("\t");
  Serial.print("Altitude at sea level: ");
  Serial.print(bmp.readAltitude(101500));
  Serial.print(" meters ");
  Serial.print("\t");
  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure());
  Serial.print(" PA");
  Serial.print("\t");
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux ");
  if (digitalRead(capteur_D) == 0)
  {
    Serial.println("Digital value : Wet");
    warning = "Digital value : wet";
    digitalWrite(buzzpin, HIGH);
  }
  else if (digitalRead(capteur_D) == 1)
  {
    Serial.println("Digital value : Dry");
    warning = "Digital value : dry";
    digitalWrite(buzzpin, LOW);
  }
  else if (digitalRead(capteur_D) == 1)
  {
    Serial.println("Digital value : Dry");
    warning = "Digital value : dry";
    digitalWrite(buzzpin, LOW);
  }
  str = String("coming from arduino: ") + " \n" + String("Temperature: ") + String(t) + String(" *C, ") + String("Humidity: ") + String(h) + String(" %, ") + String("Dew point: ") + String(dp) + String(" *C, ");
  str += String("Air quality value: ") + String(SENSOR_VALUE * 0.003) + "\n" + String("Light: ") + String(lux) + String(" LUX, ") + String("Altitude at sea level =  ") + String(bmp.readAltitude(101500)) + String(" meters, ") + String("Pressure =  ") + String(bmp.readPressure()) + String(" PA, ");
  str += String(warning);
  espSerial.println(str);
  delay(1000);
}

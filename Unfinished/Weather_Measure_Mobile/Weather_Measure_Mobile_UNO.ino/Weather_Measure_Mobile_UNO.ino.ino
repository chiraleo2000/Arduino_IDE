#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5, 6);
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <BH1750FVI.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
DHT dht(DHTPIN, DHTTYPE);
#define MQ135_PIN 0
int SENSOR_VALUE;
int val_analogique;
const int buzzpin = 4;
const int capteur_D = 8;
Adafruit_BMP085 bmp;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
void setup() {
  Serial.begin(115200);
  //Raindrop Module
  pinMode(capteur_D, INPUT);
  //buzzing
  pinMode(buzzpin, OUTPUT);
  //GY-302
  LightSensor.begin();
  dht.begin();
}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {
  // sensors
  //DHT11
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int dp = int(t - (100 - h) / 5);   //  dewpoint calculation using Celsius value
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("\t");
  Serial.print("Dew point: ");
  Serial.print(dp);
  Serial.print(" *C");
  Serial.print("\t");
  root["temp"] = t;
  root["hum"] = h;
  root["dep"] = dp;
  //MQ-135
  Serial.print("Air quality value : ");
  Serial.print(analogRead(A0));
  Serial.println("\t");
  root["gasv"] = analogRead(A0);
  //GY-302
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.print(" lux");
  Serial.print("\t");
  root["LUX"] = lux;
  //Gy-68
  int Alt = bmp.readAltitude(101500);
  int Press = (bmp.readPressure());
  Serial.print("Altitude at sea level = ");
  Serial.print(Alt);
  Serial.print(" meters");
  Serial.print("\t");
  Serial.print("Pressure = ");
  Serial.print(Press);
  Serial.print(" PA");
  Serial.print("\t");
  root["alt"] = Alt;
  root["pre"] = Press;
  //Raindrop_Module
  root["rain"] = digitalRead(capteur_D);
  //buzz
  if (digitalRead(capteur_D) == 1)
  {
    Serial.print("Digital value : wet");
    digitalWrite(buzzpin, HIGH);
    delay(2);
  }
  else if (digitalRead(capteur_D) == 0)
  {
    Serial.print("Digital value : dry");
    digitalWrite(buzzpin, LOW);
    delay(2);
  }
  if (s.available() > 0)
  {
    root.printTo(s);
  }
}

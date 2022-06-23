#include <SoftwareSerial.h>
#include <Adafruit_BMP085.h>
#include <BH1750FVI.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
DHT dht(DHTPIN, DHTTYPE);
#define MQ135_PIN 0
int SENSOR_VALUE;
int val_analogique;
const int buzzpin = 7;
const int capteur_D = 8;
Adafruit_BMP085 bmp;
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
SoftwareSerial espSerial(5, 6);
String str;
String warning;
void setup() {
  espSerial.begin(9600);
  Serial.begin(9600);
  //Raindrop Module
  pinMode(capteur_D, INPUT);
  //buzzing
  pinMode(buzzpin, OUTPUT);
  //GY-302
  LightSensor.begin();
  dht.begin();
}
void loop()
{
  //DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
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
  Serial.println(" *C");
  //MQ-135
  Serial.print("Air quality value : ");
  Serial.print(analogRead(A0));
  Serial.print("\t");
  //GY-302
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.print(" lux");
  Serial.print("\t");
  //Gy-68
  int Alt = bmp.readAltitude(101000);
  int Press = (bmp.readPressure());
  Serial.print("Altitude at sea level = ");
  Serial.print(Alt);
  Serial.print(" meters ");
  Serial.print("\t");
  Serial.print("Pressure = ");
  Serial.print(Press);
  Serial.println(" PA");
  //Raindrop_Module
  //buzz
  if (digitalRead(capteur_D) == 1)
  {
    Serial.println("Digital value : Wet");
    warning = "Digital value : wet";
    digitalWrite(buzzpin, HIGH);
    delay(2);
    digitalWrite(buzzpin, LOW);
    delay(2);
  }
  else if (digitalRead(capteur_D) == 0)
  {
    Serial.println("Digital value : Dry");
    warning = "Digital value : dry";
    digitalWrite(buzzpin, LOW);
    delay(2);
  }
  str = String("coming from arduino: ") + " \n" + String("Temperature: ") + String(t) + String(" *C, ") + String("Humidity: ") + String(h) + String(" %, ") + String("Dew point: ") + String(dp) + String(" *C, ");
  str += String("Air quality value: ") + String(analogRead(A0))+ "\n" + String("Light: ") + String(lux) + String(" LUX, ") + String("Altitude at sea level =  ") + String(Alt) + String(" meters, ") + String("Pressure =  ") + String(Press) + String(" PA, ");
  str += String(warning);
  espSerial.print(str);
  Serial.println(str);
  delay(2000);
}

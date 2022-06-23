#include "DHT.h"
#define DHTPIN A2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}
void loop() {
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
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print("Dew point: ");
  Serial.print(dp);
  Serial.println(" *C");
  delay(1000);
}

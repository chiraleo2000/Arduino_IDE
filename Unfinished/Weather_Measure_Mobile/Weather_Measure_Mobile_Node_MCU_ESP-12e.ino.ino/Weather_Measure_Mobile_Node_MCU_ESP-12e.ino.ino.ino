#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
// Replace with your network credentials
const char* ssid     = "CHIRAPATH@LEO";
const char* password = "Leo@2543";
// Set web server port number to 80
WiFiServer server(80);// Set port to 80
String header;
String Read;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
DHTesp dht;
#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
int buzzpin = 6;
int capteur_D = 5;
String warning;
void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  dht.setup(D2, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
  LightSensor.begin();
  delay(1000);
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  float dp = (t - (100 - h) / 5);   //  dewpoint calculation using Celsius value
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\t");
  Serial.print("Dew point: ");
  Serial.print(dp);
  Serial.println(" *C");
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux ");
  if (digitalRead(capteur_D) == 0)
  {
    Serial.println("Digital value : Wet");
    warning = "Wet";
    digitalWrite(buzzpin, HIGH);
  }
  else if (digitalRead(capteur_D) == 1)
  {
    Serial.println("Digital value : Dry");
    warning = "Dry";
    digitalWrite(buzzpin, LOW);
  }
  else if (h>95 && lux<30)
  {
    Serial.println("Digital value : Prepare_for_rainning");
    warning = "Prepare_for_rainning";
    digitalWrite(buzzpin, HIGH);
  }
  else if (lux<=10)
  {
    Serial.println("Digital value : Dark");
    warning = "Dark";
    digitalWrite(buzzpin, LOW);
  }
  else if (11<lux<40 && h>60)
  {
    Serial.println("Digital value : cloudy");
    warning = "cloudy";
    digitalWrite(buzzpin, LOW);
  }
  while (Serial.available()) {
    Read = Serial.read();
  }
  // Check if a client has connected
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println(F("Refresh: 2"));
            delay(2000);
            client.println();
            client.println(); //  do not forget this one
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.print("<br>Humidity: <br>");
            client.print(h);
            client.print("<br> % ,  <br>");
            client.print("Temperature: ");
            client.print(t);
            client.print(" *C ,  ");
            client.println("<br>Dew point: <br>");
            client.print(dp);
            client.print(" *C,  ");
            client.print("<br>Light: <br>");
            client.print(lux);
            client.println("<br> lux <br>");
            client.print("<br>status: <br>");
            client.print(warning);
            client.println("</html>");
          }
        }
      }
    }
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  delay(1000);
}

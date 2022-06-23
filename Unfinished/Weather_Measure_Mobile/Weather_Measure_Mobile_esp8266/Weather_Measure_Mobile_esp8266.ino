#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial s(6, 5);
#include <ArduinoJson.h>
String wo = "";
// Replace with your network credentials
const char* ssid     = "CHIRAPATH@LEO";
const char* password = "Leo@2543";
// Set web server port number to 80
WiFiServer server(80);// Set port to 80
String header; // This storees the HTTP request
void setup() {
  Serial.begin(115200);
  s.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// this will display the Ip address of the Pi which should be entered into your browser
  server.begin();
  while (!Serial) continue;
}
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int data1 = root["temp"];
  Serial.print(data1);
  Serial.print(" *C ");
  Serial.print("\t");
  Serial.print("Humidity    ");
  int data2 = root["hum"];
  Serial.print(data2);
  Serial.print("%");
  Serial.print("\t");
  Serial.print("Dew point: ");
  int data4 = root["dep"];
  Serial.print(data4);
  Serial.println(" *C");
  //MQ-135
  Serial.print("Air quality value : ");
  int data5 = root["gasv"];
  Serial.print(data5);
  Serial.print("\t");
  //GY-302
  Serial.print("Light: ");
  int data6 = root["LUX"];
  Serial.print(data6);
  Serial.print(" lux");
  Serial.print("\t");
  //Gy-68
  Serial.print("Altitude at sea level = ");
  int data7 = root["alt"];
  Serial.print(data7);
  Serial.print(" meters");
  Serial.print("Pressure = ");
  int data8 = root["pre"];
  Serial.print(data8);
  Serial.println(" PA");
  Serial.println();
  //Raindrop_Module
  int data9 = root["rain"];
  Serial.print(data9);
  WiFiClient client = server.available();   // Listen for incoming clients
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println(F("Content-Type: text/html"));
  client.println(F("Connection: close"));
  client.println(); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br>Humidity: <br>");
  client.print(data2);
  client.print(" %  ");
  client.print("<br>Temperature: <br>");
  client.print(data1);
  client.print(" *C  ");
  client.print("<br>Dew_point: <br>");
  client.print(data4);
  client.println(" *C ");
  client.print("<br>Light: <br>");
  client.print(data6);
  client.print(" LUX  ");
  client.print("<br>Pressure: <br>");
  client.print(data8);
  client.print(" PA  ");
  client.print("<br>Altitude at sea level: <br>");
  client.print(data7);
  client.print(" meters ");
  client.print("<br>Air quality value : <br>");
  client.print(data5);
  client.print(" meters ");
  client.println("</html>");
  digitalWrite(LED_BUILTIN, HIGH);
}

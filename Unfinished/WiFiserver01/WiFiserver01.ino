#include<ESP8266WiFi.h>
const char* ssid = "Mechatronics";
const char* password = "21035350";
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
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
}
void loop() {
  WiFiClient client = server.available();
}

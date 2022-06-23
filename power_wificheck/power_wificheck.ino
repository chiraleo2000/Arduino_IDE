#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
#include <ESP8266WiFi.h>
const char* ssid = "CHIRAPATH@LEO";//type your ssid
const char* password = "Leo@2543";//type your password
WiFiServer server(80);
void setup(void)
{
  Serial.begin(115200);
  while (!Serial) {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }

  uint32_t currentFrequency;

  Serial.println("Hello!");

  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) {
      delay(10);
    }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}
float  power_mW;
float  total_energy_output = 0;
float efficiency;
float times = 0;
void loop(void)
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  power_mW = ina219.getPower_mW();
  total_energy_output = (total_energy_output + (power_mW * 5));
  times = times + 5;
  efficiency = (total_energy_output / times) / 10;
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println(F("Content-Type: text/html"));
  client.println(F("Connection: close"));
  client.println(F("Refresh: 5"));
  delay(5000);
  client.println(); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br>Power generating :<br>");
  client.print(power_mW);
  client.println("  mW.");
  client.println("<br>total_energy_output : <br>");
  client.print(total_energy_output);
  client.println("  mWs.");
  client.print(total_energy_output/3600);
  client.println("  mWH.");
  client.println("<br>times<br>");
  client.print(times);
  client.println(" s.");
  client.println("<br>efficency<br>");
  client.print(efficiency);
  client.println(" percent.");
  client.println("</html>");
}

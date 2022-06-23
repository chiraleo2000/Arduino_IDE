/*
 * Sketch: ESP8266_Part8_04_AutoUpdate_DHT11
 * Intended to be run on an ESP8266
 */
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
  <meta charset='utf-8'>
  <style>
    body {font-size:100%;} 
    #main {display: table; margin: auto;  padding: 10px 10px 10px 10px; } 
    #content { border: 5px solid blue; border-radius: 15px; padding: 10px 0px 10px 0px;}
    h2 {text-align:center; margin: 10px 0px 10px 0px;} 
    p { text-align:center; margin: 5px 0px 10px 0px; font-size: 120%;}
    #time_P { margin: 10px 0px 15px 0px;}
  </style>
 
  <script> 
    function updateTime() 
    {  
       var d = new Date();
       var t = "";
       t = d.toLocaleTimeString();
       document.getElementById('P_time').innerHTML = t;
    }
 
    function updateTemp() 
    {  
       ajaxLoad('getTemp'); 
    }
 
    var ajaxRequest = null;
    if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
    else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
 
    function ajaxLoad(ajaxURL)
    {
      if(!ajaxRequest){ alert('AJAX is not supported.'); return; }
 
      ajaxRequest.open('GET',ajaxURL,true);
      ajaxRequest.onreadystatechange = function()
      {
        if(ajaxRequest.readyState == 4 && ajaxRequest.status==200)
        {
          var ajaxResult = ajaxRequest.responseText;
          var tmpArray = ajaxResult.split("|");
          document.getElementById('temp_C').innerHTML = tmpArray[0];
          document.getElementById('temp_F').innerHTML = tmpArray[1];
          document.getElementById('hmd').innerHTML = tmpArray[2];
        }
      }
      ajaxRequest.send();
    }
 
    var myVar1 = setInterval(updateTemp, 5000);  
    var myVar2 = setInterval(updateTime, 1000);  
 
  </script>
 
 
  <title>Temperature & Humidy Monitor</title>
 </head>
 
 <body>
   <div id='main'>
     <h2>Temperature & Humidity Monitor</h2>
     <div id='content'> 
       <p id='P_time'>Time</p>
       <h2>Temperature</h2>
       <p> <span id='temp_C'>--.-</span> &deg;C &nbsp;-&nbsp; <span id='temp_F'>--.-</span> &deg;F </p>
       <h2>Humidity</h2>
       <p> <span id='hmd'>--</span> % </p>
     </div>
   </div> 
 </body>
</html>
)====="; 
 
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

// change these values to match your network
char ssid[] = "CHIRAPATH@LEO";       //  your network SSID (name)
char pass[] = "Leo@2543";          //  your network password
 
#include "DHT.h"
#define DHTPIN D1   // what digital pin we're connected to
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
float tempF = 0;
float tempC = 0;
float humid = 0;

String teF;
String teC;
String hum;
 
WiFiServer server(80);
String request = "";
 
 
void setup() 
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial started at 115200");
    Serial.println();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
    dht.begin();
  
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
    display.clearDisplay();
    display.setTextSize(4);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(40, 20);
    // Display static text
    display.println("DHT Sensor");
    display.display(); 
    // Connect to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
 
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");
    delay(1000);
    display.clearDisplay();
} // void setup()
 
 
void loop() 
{
    WiFiClient client = server.available();     // Check if a client has connected
    if (!client)  {  return;  }
 
    request = client.readStringUntil('\r');     // Read the first line of the request
 
    Serial.println(request);
    Serial.println("");

    humid = dht.readHumidity();
    tempC = dht.readTemperature();        // Read temperature as Celsius (the default)
    tempF = dht.readTemperature(true);    // Read temperature as Fahrenheit (isFahrenheit = true)

    hum = String(humid);
    teC = String(tempC);        // Read temperature as Celsius (the default)
    teF = String(tempF);    // Read temperature as Fahrenheit (isFahrenheit = true)

    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(40, 10);
    display.print("Humidity: ");
    display.print(hum);
    display.println("relative percentages."); 
    display.setCursor(80, 10);
    display.print("Temperature: "); 
    display.print(teC);
    display.print("*C , ");
    display.print(teF);
    display.println("*F.");
    display.display();

    if ( request.indexOf("getTemp") > 0 )
     { 
          Serial.println("getTemp received");
 
          // Reading temperature or humidity takes about 250 milliseconds!
          // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
          humid = dht.readHumidity();
          tempC = dht.readTemperature();        // Read temperature as Celsius (the default)
          tempF = dht.readTemperature(true);    // Read temperature as Fahrenheit (isFahrenheit = true)
          
          if ( !isnan(humid) && !isnan(tempC) && !isnan(tempC) )
          {
              client.print( header );
              client.print( tempC );   client.print( "|" );  client.print( tempF );   client.print( "|" );  client.print( humid ); 
              Serial.println("data sent"); 
          }
          else
          {
            Serial.println("Error reading the sensor");
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE, BLACK);
            display.setCursor(60, 20);
            display.print("Error reading the sensor");
          }
      }

    else
    {
      client.flush();
      client.print( header );
      client.print( html_1 ); 
      Serial.println("New page served");
    }
 
    delay(5);
 
  // The client will actually be disconnected when the function returns and the 'client' object is destroyed

} 

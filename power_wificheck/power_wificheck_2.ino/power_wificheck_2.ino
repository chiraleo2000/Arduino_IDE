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

    function updatepower() 
    {  
       ajaxLoad('getPower'); 
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
          var powerinput = ajaxResult.split("|");
          document.getElementById('power').innerHTML = powerinput[0];
          document.getElementById('total_output').innerHTML = powerinput[1];
          document.getElementById('Voltage').innerHTML = powerinput[2];
          document.getElementById('Current').innerHTML = powerinput[3];
          document.getElementById('times').innerHTML = powerinput[4];
          document.getElementById('last_total_output').innerHTML = powerinput[5];
          document.getElementById('last_times').innerHTML = powerinput[6];
        }
      }
      ajaxRequest.send();
    }

    var myVar1 = setInterval(updatepower, 1000);  
    var myVar2 = setInterval(updateTime, 1000);  

  </script>


  <title>WiFi_Power_Measurement_station</title>
 </head>

 <body>
   <div id='main'>
     <h2>WiFi_Power_Measurement_station</h2>
     <div id='content'> 
       <p id='P_time'>Time</p>
       <h2>Power generating :</h2>
       <p> <span id='power'>--.-</span> mW </p>
       <h2>Total_energy_output: </h2>
       <p> <span id='total_output'>--</span> mWH </p>
       <h2>Voltage_Generating: </h2>
       <p> <span id='Voltage'>--</span> V </p>
       <h2>Current_Generating:: </h2>
       <p> <span id='Current'>--</span> mA </p>
       <h2>Time_generating: </h2>
       <p> <span id='times'>--.-</span> s </p>
       <h2>Last_Total_energy_output: </h2>
       <p> <span id='last_total_output'>--</span> mWH </p>
       <h2>Last_Time_generating: </h2>
       <p> <span id='last_times'>--.-</span> s </p>
     </div>
   </div> 
 </body>
</html>
)====="; 

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
// change these values to match your network
char ssid[] = "CHIRAPATH@LEO";       //  your network SSID (name)
char pass[] = "Leo@2543";          //  your network password
float power_mW = 0;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float total_energy_output = 0;
float times = 0;
float last_total_energy_output = 0;
float last_times = 0;
WiFiServer server(80);
String request = "";


void setup() 
{
    Serial.begin(115200);
    Serial.println();
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
    while (1) { delay(10); }
  }
    Serial.println("Serial started at 115200");
    Serial.println();
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

} // void setup()


void loop() 
{
    WiFiClient client = server.available();     // Check if a client has connected
    if (!client)  {  return;  }

    request = client.readStringUntil('\r');     // Read the first line of the request

    Serial.println(request);
    Serial.println("");

    if ( request.indexOf("getPower") > 0 )
     { 
          Serial.println("getPower received");
            shuntvoltage = ina219.getShuntVoltage_mV();
            busvoltage = ina219.getBusVoltage_V();
            current_mA = ina219.getCurrent_mA();
            loadvoltage = busvoltage + (shuntvoltage / 1000);
            power_mW = ina219.getPower_mW();
            total_energy_output += (power_mW)/3600;
            times = times + 1;
            last_total_energy_output = last_total_energy_output;
            last_times = last_times;
            if ( !isnan(power_mW) && !isnan(total_energy_output) && !isnan(times) )
          {
              client.print( header );
              client.print( power_mW );   client.print( "|" );  client.print( total_energy_output );   client.print( "|" ); client.print( loadvoltage );   client.print( "|" );client.print( current_mA ); client.print( "|" ); client.print( times );   client.print( "|" );  client.print( last_total_energy_output );   client.print( "|" );  client.print( last_times );
              Serial.println("data sent");
          }
          else
          {
              Serial.println("Error reading the sensor");
          }
     }

     else
     {
        client.flush();
        client.print( header );
        last_total_energy_output = total_energy_output + last_total_energy_output;
        last_times = times + last_times;
        times = 0;
        total_energy_output = 0;
        
        client.print( html_1 ); 
        Serial.println("New page served");
     }

    delay(5);


  // The client will actually be disconnected when the function returns and the 'client' object is destroyed

} 

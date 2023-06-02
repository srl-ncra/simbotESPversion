

// Import required libraries
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>



#define Rx 16
#define Tx 17
int coming_value = 0;
int x[10];
int y[10];
int angle[10];
int temp_var=1;
int arr_size=-1;

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);




void setup()
{ 
  
  
  
  
  Serial.begin(115200);

 
  
  Serial2.begin(9600, SERIAL_8N1, Rx, Tx);
  // Serial2.write(4800);

// Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);


for(int i=1;i<10;i++)
  {
    x[i]=-1;
    y[i]=-1;
    angle[i]=-1;
  }

// For Coordinate Size

 server.on("/coordinate_size", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(arr_size).c_str());
  });



// For Coordinate point 0

 server.on("/coordinatex0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[0]).c_str());
  });

   server.on("/coordinatey0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[0]).c_str());
  });

   server.on("/coordinate_angle0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[0]).c_str());
  });



// For Coordinate point 1

 server.on("/coordinatex1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[1]).c_str());
  });

   server.on("/coordinatey1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[1]).c_str());
  });

   server.on("/coordinate_angle1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[1]).c_str());
  });




// For Coordinate point 2

 server.on("/coordinatex2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[2]).c_str());
  });

   server.on("/coordinatey2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[2]).c_str());
  });

   server.on("/coordinate_angle2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[2]).c_str());
  });




// For Coordinate point 3

 server.on("/coordinatex3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[3]).c_str());
  });

   server.on("/coordinatey3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[3]).c_str());
  });

   server.on("/coordinate_angle3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[3]).c_str());
  });



// For Coordinate point 4

 server.on("/coordinatex4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[4]).c_str());
  });

   server.on("/coordinatey4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[4]).c_str());
  });

   server.on("/coordinate_angle4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[4]).c_str());
  });



// For Coordinate point 5

 server.on("/coordinatex5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x[5]).c_str());
  });

   server.on("/coordinatey5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y[5]).c_str());
  });

   server.on("/coordinate_angle5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(angle[5]).c_str());
  });






  // Start server
  server.begin();
 
}

void loop()
{ 
 
  /*  Serial2.write(1);  //Forward
    Serial2.write(10);
    delay(2000);
    Serial2.write(2);  //Forward
    Serial2.write(10);
    delay(2000);
    Serial2.write(3);  //Forward
    Serial2.write(30);
    delay(2000);
  *//*
  coming_value=Serial2.read();
  if(coming_value==1)
  x=coming_value;
  coming_value=Serial2.read();
  if(coming_value==2)
  y=coming_value;
  coming_value=Serial2.read();
  if(coming_value==3)
  angle=coming_value;




  Serial.println("So x is");
  Serial.println(x);

  Serial.println("So y is");
  Serial.println(y);
*/
if(arr_size<=0)
{

  arr_size=Serial2.read();
  Serial.println("So Size is ");
  Serial.println(arr_size);
  
}

else
{
while(arr_size!=-1 && temp_var!=arr_size)
{  x[temp_var]=Serial2.read();
 y[temp_var]=Serial2.read();
 angle[temp_var]=Serial2.read();
 
  Serial.println("So values are ");
  Serial.println(arr_size);
  Serial.println(x[temp_var]);
  Serial.println(y[temp_var]);
  Serial.println(angle[temp_var]);


temp_var++;
}
}

/*
if(temp_var==arr_size-1)
{
for(int i=1;i<arr_size;i++)
{
Serial.println("For i" + String(i));
Serial.println(x[i]);
Serial.println(y[i]);
Serial.println(angle[i]);

//       Serial.println("X: " + x[i] + " *C - Y: " + y[i] + " % - Angle: " + angle[i] + " hPa");

}
  
}*/
  
  
  /* delay(2000);
    Serial2.write('R');  //Reverse
    delay(50);
    Serial2.write('L');  //Left turn
    delay(2000);
    Serial2.write('r');  //Right turn
    delay(50);
    Serial2.write('S');  //Stop SIMBOT
    delay(2000);
  */



  //Serial.println(  char(Serial2.read()  ) );

}

String coordinates(int i)
{
  if(i==1)
  return String(x[temp_var]);
  if(i==2)
  return String(y[temp_var]);
  if(i==3)
  return String(angle[temp_var]);
  
}

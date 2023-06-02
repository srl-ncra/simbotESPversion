
#include <WiFi.h>
#include <HTTPClient.h>

//Software serial
#include <SoftwareSerial.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
//coordinate 0
const char* serverSize = "http://192.168.4.1/coordinate_size";
String serverX[10]; 
String serverY[10];
String serverAngle[10];
#include <Wire.h>

#define Rx 16
#define Tx 17

String arr_size;
String x[10];
String y[10];
String angle[10];
bool size_taken=false;
bool sending=false;
bool size_sent=false;
bool Initial=false;
int temp_var=1;

int sizei=-1;
int xi;
int yi;
int anglei;

int k=1;

unsigned long previousMillis = 0;
const long interval = 5000; 

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, Rx, Tx);


  for(int i=0;i<10;i++)
  {
  serverX[i]  = "http://192.168.4.1/coordinatex" + String(i);
  serverY[i]  = "http://192.168.4.1/coordinatey" + String(i);
  serverAngle[i]  = "http://192.168.4.1/coordinate_angle" + String(i);
 
  }
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  for (int i=0;i<10;i++)
  {
    x[i]=String(NULL);
    y[i]=String(NULL);
    
  }
}

void loop() {
  unsigned long currentMillis = millis();

  
    

  if(currentMillis - previousMillis >= interval) {

  while(!(WiFi.status()== WL_CONNECTED) && Initial==false)
  {
    
  }

    Initial=true;
    while(size_taken==false && sizei <= 0)
    {
arr_size = httpGETRequest(serverSize);
sizei=arr_size.toInt();
if(sizei>0)
{ 
  Serial.println("The size is");
  Serial.println(sizei);
  Serial.println("");
  Serial.println("");
  Serial2.write(sizei);

size_taken=true;


}
if(sizei==0 || sizei==-1)
size_taken=false;

    }

    
     // Check WiFi connection status
    if(size_taken){ 
     
      while((temp_var != arr_size.toInt()))
    { 
       
      x[temp_var] = httpGETRequest(serverX[temp_var].c_str());
      y[temp_var] = httpGETRequest(serverY[temp_var].c_str());
      angle[temp_var] = httpGETRequest(serverAngle[temp_var].c_str());
    

     xi=x[temp_var].toInt();
     yi=y[temp_var].toInt();
     anglei=angle[temp_var].toInt();
     while(xi<0)
     {
      x[temp_var] = httpGETRequest(serverX[temp_var].c_str());
      xi=x[temp_var].toInt();
      }
      while(yi<0)
     {
      y[temp_var] = httpGETRequest(serverY[temp_var].c_str());
      yi=y[temp_var].toInt();
      }
      while(anglei<0)
     {
      angle[temp_var] = httpGETRequest(serverAngle[temp_var].c_str());
      anglei=angle[temp_var].toInt();
      }
       Serial.println("Sending Values");
     Serial.println("x sent = ");
     Serial.println(x[temp_var].toInt());
     Serial.println("y sent = ");
     Serial.println(y[temp_var].toInt());
     Serial.println("angle sent =");
     Serial.println(angle[temp_var].toInt());
     Serial2.write(xi);
     Serial2.write(yi);
     Serial2.write(anglei);     
     Serial.println("X: " + x[temp_var] + " *C - Y: " + y[temp_var] + " % - Angle: " + angle[temp_var] + " hPa");
      
      temp_var++;
    }  
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    
    }
    else {
      Serial.println("WiFi Disconnected");


    }


    
  }

  

  
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

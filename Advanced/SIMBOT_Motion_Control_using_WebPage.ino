// Load Wi-Fi library
#include <WiFi.h>
#include<analogWrite.h>
// Replace with your network credentials
const char* ssid     = "SimBotTeleop";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

//Left and right Motor Enable Pins
int R_Motor=14; //5 version 1.0
int L_Motor=26;  //6 version 1.0

// PWM Pins for Left and Right Motors
int Right_PWM = 27; //10 version 1.0
int Left_PWM = 4;   //9 version 1.0

/*Pulse Width Modulation PWM
5v
0% duty cycle---- 0=5v
25% duty cycle---- 64=4v
50% duty cycle---- 127=2.5v
75% duty cycle---- 191=1v
100% duty cycle---- 255=0v
*/
/*0v
0% duty cycle---- 0=0v
25% duty cycle---- 64=1v
50% duty cycle---- 127=2.5v
75% duty cycle---- 191=4v
100% duty cycle---- 255=5v
*/

int F_race = 0;//0 max
int R_race=255;// 255 max
#define Forward 1
#define Reverse 0
//////////////////////



// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "forward";
String output27State = "right";


void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  // put your setup code here, to run once:
pinMode(R_Motor,OUTPUT);
pinMode(L_Motor,OUTPUT);
pinMode(Right_PWM,OUTPUT);
pinMode(Left_PWM,OUTPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
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
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/forward") >= 0) {
              Serial.println("Moving Forward");
              output26State = "forward";
              forward();
            } 
            
            else if (header.indexOf("GET /26/reverse") >= 0) {
              Serial.println("Reverse");
              output26State = "reverse";
              reverse();
            }
            else if (header.indexOf("GET /27/right") >= 0) {
              Serial.println("Right");
              output27State = "right";
              right();
            }
            else if (header.indexOf("GET /27/left") >= 0) 
            {
              Serial.println("left");
              output27State = "left";
              left();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>SimBot Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Moving " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="forward") {
              client.println("<p><a href=\"/26/reverse\"><button class=\"button\">reverse</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/forward\"><button class=\"button button2\">forward</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Moving " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="right") {
              client.println("<p><a href=\"/27/left\"><button class=\"button\">left</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/right\"><button class=\"button button2\">right</button></a></p>");
            }
            client.println("</body></html>");


            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}


//For turning the motor weels in a forward direction
void forward()
{
  //Turning right weels  
digitalWrite(R_Motor, Forward);
analogWrite(Right_PWM,F_race);//0 max----255 min
//Turning left weels  
digitalWrite(L_Motor, Forward);     
analogWrite(Left_PWM,F_race);
}

//For turning the motor weels in a reverse direction
void reverse()
{
  //Turning right weels  
digitalWrite(R_Motor, Reverse);
analogWrite(Right_PWM,R_race);//255 max----0 min
//Turning left weels  
digitalWrite(L_Motor,Reverse);     
analogWrite(Left_PWM,R_race);
}
//For stopping the rotation of both left and right weels
void Stop()
{
 digitalWrite(R_Motor, Reverse);
analogWrite(Right_PWM,0);//255 max----0 min
//Turning left weels  
digitalWrite(L_Motor,Reverse);     
analogWrite(Left_PWM,0);
}
//For rotating the motors in the rightward direction
void right()
{
  //Turning right weels  
digitalWrite(R_Motor, Reverse);
analogWrite(Right_PWM,127);//127=50% duty cycle=2.5v
//Turning left weels  
digitalWrite(L_Motor, Forward);     
analogWrite(Left_PWM,127);
}
//For rotating the motors in the leftward direction
void left()
{
  //Turning right weels  
digitalWrite(R_Motor, Forward);
analogWrite(Right_PWM,127);//127=50% duty cycle=2.5v
//Turning left weels  
digitalWrite(L_Motor, Reverse);     
analogWrite(Left_PWM,127);
}

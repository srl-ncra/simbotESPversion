//****************Code Developed by Muneeb RDE BrainSwarm****************//
#include "BluetoothSerial.h"
#include<analogWrite.h>

//Left and right Motor Enable Pins
int R_Motor=14; //5 version 1.0
int L_Motor=26;  //6 version 1.0
char t;
// PWM Pins for Left and Right Motors
int Right_PWM = 27; //10 version 1.0
int Left_PWM = 4;   //9 version 1.0

int F_race = 200;
int R_race=50;
#define Forward 0
#define Reverse 1
/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);

  pinMode(R_Motor,OUTPUT);
  pinMode(L_Motor,OUTPUT);
  pinMode(Right_PWM,OUTPUT);  
  pinMode(Left_PWM,OUTPUT);

  SerialBT.begin("SimBot");
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  if (SerialBT.available())
  {
    t = SerialBT.read();
   Serial.println(SerialBT.read());
  }
  
    if (t == 'F')
    {
     forward();
     Serial.write("Moving Forward");
    }
    else if (t == 'B')
    {
     reverse();
     Serial.write("Moving Backward");
    }
    else if (t == 'L')
    {
     left();
     Serial.write("Moving Left");
    }
    else if (t =='R')
    {
     right();
     Serial.write("Moving Right");
    }
    else if (t == 'S')
    {
     Stop();
     Serial.write("SimBot Stops");
    }
}

//Forward------Left----Right---Reverse--Functions---

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
 digitalWrite(R_Motor, Forward);
analogWrite(Right_PWM,0);//255 max----0 min
//Turning left weels  
digitalWrite(L_Motor,Forward);     
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

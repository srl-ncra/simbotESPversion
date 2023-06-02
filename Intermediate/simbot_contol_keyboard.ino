//****************Code Developed by Muneeb RDE BrainSwarm****************//
#include<analogWrite.h>
/*This code manualy controlls the rotation of the motor either moving
 in theforward direction,reverse,right,left or to stop the motors
*/


//Left and right Motor Enable Pins
int R_Motor=14;
int L_Motor=26;

// PWM Pins for Left and Right Motors
int Right_PWM = 27;
int Left_PWM = 4;

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

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);// Giving the baud rate for the communication,Rx-Tx UART Communication
pinMode(R_Motor,OUTPUT);
pinMode(L_Motor,OUTPUT);
pinMode(Right_PWM,OUTPUT);
pinMode(Left_PWM,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available()==1)
  {
char val=Serial.read();
Serial.print(val);

if (val=='F')
{
forward();  
}
else if(val=='B')
{
reverse();  
}
else if(val=='R')
{
right();  
}
else if(val=='L')
{
left();  
}
else if(val=='S')
{
Stop();  
}


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

// Read Encoder Tick Values from Wheel Encoders


//****************Code Developed by Muneeb RDE BrainSwarm****************//
#include<analogWrite.h>
/*The objective of this code is to become familiar with the rotatory encoders & to 
read the change in a values on a serial monitor with a blinking leds on the board*/
  
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
  // Left and Right Motor Encoder Inputs
 #define L_encoder 25
 #define R_encoder 13
  // LED Outputs
 #define led_T 18
 #define led_B 19
 
 int counter = 0; 
 int counter1=0;
 int previousState_L_encoder;
 int currentState_L_encoder;
 int previousState_R_encoder; 
 int currentState_R_encoder;

 
 void setup() { 
   
   // Set encoder pins as inputs  
   pinMode (L_encoder,INPUT);
   pinMode (R_encoder,INPUT);
   // Set LED pin as output
   pinMode (led_T,OUTPUT);  
   pinMode (led_B,OUTPUT);   
   // Setup Serial Monitor
   Serial.begin (9600);
   pinMode(R_Motor,OUTPUT);
pinMode(L_Motor,OUTPUT);
pinMode(Right_PWM,OUTPUT);
pinMode(Left_PWM,OUTPUT);
   // Read the initial state of encoders
   // Assign to previousState variable
   previousState_L_encoder = digitalRead(L_encoder);
   previousState_R_encoder = digitalRead(R_encoder);
 }

  
 void loop()
{ 
   //Functions to read the left and right encoders and to blink the top led for the left encoder and the bottom for the right encoder
    left_Encoder_Read();
    right_Encoder_Read();  
}


/*Function to read the left encoder pulses and blinks an led*/

void left_Encoder_Read(){
//Turning left weel 
digitalWrite(L_Motor, Forward);     
analogWrite(Left_PWM,F_race);

    // Read the current state of L_encoder
   currentState_L_encoder = digitalRead(L_encoder);
   // If the previous and the current state of the left encoder are different then a pulse has occured
   if (currentState_L_encoder != previousState_L_encoder)
   {  
 // Encoder is rotating
      digitalWrite(led_T, HIGH);
      counter ++;
     }
 else
     {
      //Encoder stops rotating
      digitalWrite(led_T, LOW);
     }
     // Update previousState of left encoder with the current state
      previousState_L_encoder = currentState_L_encoder; 
     Serial.print("L_Encoder: ");
     Serial.print(" -- Value: ");
     Serial.print(counter);
  }


/*Function to read the right encoder pulses and blinks an led*/

void right_Encoder_Read(){ 
  //Turning right weels  
digitalWrite(R_Motor, Forward);
analogWrite(Right_PWM,F_race);//0 max----255 min
  // Read the current state of R_encoder
   currentState_R_encoder = digitalRead(R_encoder);
  // If the previous and the current state of the left encoder are different then a pulse has occured     
if(currentState_R_encoder != previousState_R_encoder)
     { 
       
     // If the R_encoder state is different than the R_encoder state then 
            // Encoder is rotating
      digitalWrite(led_B, HIGH);
      counter1 ++;
     }
else
     {
      // Encoder stops rotating
      digitalWrite(led_B, LOW);
     }
      // Update previousState of Right encoder with the current state
      previousState_R_encoder = currentState_R_encoder; 
      Serial.print("\t\t"); 
     Serial.print("R_Encoder: ");
     Serial.print(" -- Value: ");
     Serial.println(counter1);    
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

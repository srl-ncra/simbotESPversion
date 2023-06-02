// Obstacle Avoidance using SIMBOT-ESP

#include<analogWrite.h>
// Basic test of Mona robot including proximity sensors and open-loop motion control

// pin config for basic platform test
// Motors
int Motor_right_PWM = 27; //10;  //   0 (min speed) - 255 (max speed) // esp pin 26
int Motor_right_direction = 14; //5;  //    0 Forward - 1 Reverse      //  esp pin 27
int Motor_left_PWM = 4; //9;    //   0 (min speed) - 255 (max speed) // esp pin 17
int Motor_left_direction = 26; //6;   //   0 Forward - 1 Reverse      //  esp pin 14
#define Forward 0         //
#define Reverse 1         //
// LED
int LED1 = 18; //13;           // esp pin 18
int LED2 = 19;//12;            // esp pin 19  
int IR_enable = 2; //4;         // esp pin  9      
int IR_threshold = 3000; // 0 white close obstacle -- 1023 no obstacle


void setup() {
// initialize serial communication at 9600 bits per second:
 Serial.begin(9600);
// initialize Ports
  pinMode(Motor_left_PWM,  OUTPUT);
  pinMode(Motor_right_PWM, OUTPUT);
  pinMode(Motor_right_direction, OUTPUT);
  pinMode(Motor_left_direction,  OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(IR_enable, OUTPUT);
} 

void forward(){
  analogWrite(Motor_right_PWM,200); // right motor
  digitalWrite(Motor_right_direction,Forward); //right
  analogWrite(Motor_left_PWM, 241); // left 
  digitalWrite(Motor_left_direction,Forward); //left
  Serial.println("FWD");
}

void reverse(int delay_time){
  
  analogWrite(Motor_right_PWM,50 ); // right motor
  digitalWrite(Motor_right_direction,Reverse); //right
  analogWrite(Motor_left_PWM, 50); // left 
  digitalWrite(Motor_left_direction,Reverse); //left
  delay(delay_time);
}

void right(int delay_time){
  reverse(50);
  analogWrite(Motor_right_PWM,50 ); // right motor
  digitalWrite(Motor_right_direction,Reverse); //right
  analogWrite(Motor_left_PWM, 200); // left 
  digitalWrite(Motor_left_direction,Forward); //left  
  delay(delay_time);
}

void left(int delay_time){
  reverse(50);
  analogWrite(Motor_right_PWM,200 ); // right motor
  digitalWrite(Motor_right_direction,Forward); //right
  analogWrite(Motor_left_PWM, 50); // left 
  digitalWrite(Motor_left_direction,Reverse); //left
  delay(delay_time);
}

// Variables for 5 IR proximity sensors 
int IR_right,IR_right_front,IR_front,IR_left_front,IR_left;

void IR_proximity_read(){    // read IR sensors 
  int n=5;  // average parameter
  digitalWrite(IR_enable, HIGH);  //IR Enable
  IR_right=0;
  IR_right_front=0;
  IR_front=0;
  IR_left_front=0;
  IR_left=0;
  for (int i=0;i<n;i++){
    IR_right+=analogRead(36);
    IR_right_front+=analogRead(34);
    IR_front+=analogRead(32);
    IR_left_front+=analogRead(33);
    IR_left+=analogRead(35);
    delay(5);
  }
  IR_right/=n;
  IR_right_front/=n;
  IR_front/=n;
  IR_left_front/=n;
  IR_left/=n; 
}

// obstacle avoidance
void Obstacle_avoidance(){
  if (IR_front<IR_threshold){
      digitalWrite(LED2,HIGH);
      reverse(300);
      right(500);
      digitalWrite(LED2,LOW);
  }
  if (IR_right<IR_threshold || IR_right_front<IR_threshold ){
      digitalWrite(LED2,HIGH);
      left(500);
      digitalWrite(LED2,LOW);
  } else {
      if (IR_left<IR_threshold || IR_left_front<IR_threshold ){
          digitalWrite(LED2,HIGH);
          right(500);
          digitalWrite(LED2,LOW);
      } else forward();
  }  
}

// send IR readings to Serial Monitor
void Send_sensor_readings(){
 Serial.print(IR_right);
 Serial.print(',');
 Serial.print(IR_right_front);
 Serial.print(',');
 Serial.print(IR_front);
 Serial.print(',');
 Serial.print(IR_left_front);
 Serial.print(',');
 Serial.println(IR_left);  
}


// the loop routine runs over and over again forever:
void loop() {

 digitalWrite(LED1,HIGH); //Top LED
 IR_proximity_read();
 Send_sensor_readings(); 
 Obstacle_avoidance();
 digitalWrite(LED1,LOW); //Top LED

 delay(100);        // delay in between reads for stability
}

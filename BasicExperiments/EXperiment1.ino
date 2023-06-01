// Basic Practice Code (LED Blink)

//****************Code Developed by Muneeb RDE BrainSwarm****************//
void setup()
{
  // put your setup code here, to run once:
pinMode(18,OUTPUT);
pinMode(19,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(18,HIGH);
digitalWrite(19,HIGH);
delay(1000);
digitalWrite(18,LOW);
digitalWrite(19,LOW);
delay(1000);
}

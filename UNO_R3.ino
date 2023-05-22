#include<AFMotor.h>
#include<Servo.h>
Servo name_servo;
int servo_position=0;
const int ldrPin = A1;
void setup()
{
  // put your setup code here, to run once:
  name_servo.attach(10);
  pinMode(ldrPin, INPUT);
}

void loop()
{
  name_servo.write(180);
  int ldrStatus = analogRead(ldrPin);
  if(ldrStatus>=700)
  {
    for(servo_position=30;servo_position<=90;servo_position +=1)
    {
      name_servo.write(servo_position);
      delay(40);
    }
    for(servo_position=90;servo_position>=30;servo_position -=1)
    {
      name_servo.write(servo_position);
      delay(50);
    }
  }
  else if(ldrStatus<=30)
  {
    Serial.print(ldrStatus);
  }
}

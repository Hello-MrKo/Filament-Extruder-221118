
#include <Servo.h>

Servo myservo;  // create servo object to control a servo motor
float pos = 0;    // variable to store the servo motor position

int M1PUL=9;    //step motor 1  Pulse pin
int M1DIR=8;   //step motor 1  Direction pin

void setup() {  
  pinMode (M1PUL, OUTPUT);     //step motor pulse 출력 설정 
  pinMode (M1DIR, OUTPUT);     //step motor direction 출력 설정 

  myservo.attach(10);  // attaches the servo motor on pin 2 to the servo object
  
}
 
void loop() {
        digitalWrite(M1DIR,LOW);              // 모터 회전 방향 설정 
    for (pos = 0; pos <= 180; pos += 0.001) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    digitalWrite(M1PUL,HIGH);
    delayMicroseconds(50);              // 모터 회전 속도
    digitalWrite(M1PUL,LOW); 
    delayMicroseconds(50);              // 모터 회전 속도         
  }  
  for (pos = 180; pos >= 0; pos -= 0.001) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    digitalWrite(M1PUL,HIGH);
    delayMicroseconds(50);              // 모터 회전 속도
    digitalWrite(M1PUL,LOW); 
    delayMicroseconds(50);              // 모터 회전 속도       
  }
 }


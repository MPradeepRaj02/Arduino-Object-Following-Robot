//1 OCT 2020
//Just An Object Follower -> J.A.O.F
//      < M.P.R >

#include <Servo.h>
#include <AFMotor.h>

#define echo A0
#define trig A1
#define left A2
#define right A3

Servo servo;
int i;
long duration ;
int distance ;

AF_DCMotor motor3(3,MOTOR34_1KHZ);  //L
AF_DCMotor motor4(4,MOTOR34_1KHZ);  //R

void setup()  {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  Serial.begin(9600);
  servo.attach(10);
}

void loop() {
  
  distance = calculateDistance();
  servo.write(0);
  servo.write(180);
    
  Serial.println(distance);
  
  if(distance<=15 && distance>0) {
    servo.write(90);
    motor3.run(FORWARD);
    motor3.setSpeed(180);
    motor4.run(FORWARD);
    motor4.setSpeed(180);
  }

  else if(digitalRead(left)==0 && !analogRead(right)==0) {//L
    servo.write(0);
    motor3.run(FORWARD);
    motor3.setSpeed(150);
    motor4.run(BACKWARD);
    motor4.setSpeed(10);
    
    delay(150);
  }

  else if(!digitalRead(left)==0 && digitalRead(right)==0) {//R
    servo.write(180);
    motor3.run(BACKWARD);
    motor3.setSpeed(10);
    motor4.run(FORWARD);
    motor4.setSpeed(150);
   
    delay(150);
  }

  else {
    servo.write(90);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
    delay(500);   
  }
}

int calculateDistance() {
    digitalWrite(trig,HIGH);
    delayMicroseconds(1);
    digitalWrite(trig,LOW);

    duration = pulseIn(echo,HIGH);
    distance = duration*0.034/2;
    return distance;
  }

// Motor pins
#define motor1  6 //LEFT MOTOR
#define DIRA1  4  //FORWARD LEFT
#define DIRB1  5  //BACKWARD LEFT
#define motor2 9  //RIGHT MOTOR
#define DIRA2 11  //FORWARD RIGHT 
#define DIRB2 10  //BACKWARD RIGHT

//US Sensor pins
#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// Initializing movement parameters
long dist;
int speedL = 0;
int speedR = 0;

void leftspeed(int x){
  if (x<0){
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRB1,LOW);
  speedL = abs(x);
  }
  if (x>0){
  digitalWrite(DIRB1,HIGH);
  digitalWrite(DIRA1,LOW);
  speedL = abs(x);
  }

}

void rightspeed(int x){
  if (x<0){
  digitalWrite(DIRA2,HIGH);
  digitalWrite(DIRB2,LOW);
  speedR = abs(x);
  }
  if (x>0){
  digitalWrite(DIRB2,HIGH);
  digitalWrite(DIRA2,LOW);
  speedR = abs(x);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(motor1,OUTPUT);
  pinMode(DIRA1,OUTPUT);
  pinMode(DIRB1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(DIRA2,OUTPUT);
  pinMode(DIRB2,OUTPUT);
  Serial.println("Group Project");
}

//FOR PREDETERMINED PATH
//Find whatever a 90 deg turn is 
//turnRight(), turnLeft()
//for 
void loop() {

   dist=sr04.Distance();
   Serial.println(dist);
   if (dist < 60){
    leftspeed(-200);
    rightspeed(-200 + (6*dist));
   }
   if (dist > 60){
    leftspeed(-200);
    rightspeed(-200);
   }
   Serial.print(".   ");
   //Serial.print();
   /*
   if (dist >= 20 && dist <= 100){

    //leftspeed(map(dist,20,200,0,100));
    rightspeed()
   }
*/
  analogWrite(motor1,speedL);
  analogWrite(motor2,speedR);
}

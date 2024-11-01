#define LEFT_Motor 6                    //VCC pin on Motor 1
#define LEFT_Forward 4                  //Direction pin on Motor 1
#define LEFT_Backward 5                 //Direction pin on Motor 1
#define RIGHT_Motor 9                   //VCC pin on Motor 2
#define RIGHT_Forward 11                //Direction pin on Motor 2
#define RIGHT_Backward 10               //Direction pin on Motor 2

#include "SR04.h"                       //US Sensor declarations
#define TRIG_PIN 2  
#define ECHO_PIN 3  
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN); 

#define colorpin 7                      //IR Pin & Initialization
int color = 0;

long dist;                              //Distance variable

int LEFT_speed = 0;                     //Initialize motor speeds to zero 
int RIGHT_speed = 0; 

#define buttonPin 8
bool codestate = true;                  //true: default, false: custom pathway

void setup() {

  Serial.begin(9600);
  pinMode(LEFT_Motor,OUTPUT);           //Define motor pins
  pinMode(LEFT_Forward,OUTPUT);
  pinMode(LEFT_Backward,OUTPUT);
  pinMode(RIGHT_Motor,OUTPUT);
  pinMode(RIGHT_Forward,OUTPUT);
  pinMode(RIGHT_Backward,OUTPUT);

  pinMode(colorpin,INPUT);              //defines the ir sensor pin

  pinMode(buttonPin,INPUT);             //defines the button pin
}

void loop() {

  if (digitalRead(buttonPin)==1 && codestate == false){
    codestate = true;
    delay(250);
  }
  if (digitalRead(buttonPin)==1 && codestate == true){
    codestate = false;
    delay(250);
  }

  
  if (codestate == true){
    color = digitalRead(colorpin);
    dist = sr04.Distance();                     //Distance value given by US Sensor
    Serial.println(dist);                       //Print distance(cm) in Serial Monitor
    if (color == LOW){
      moveStop();
    }
    else{
      if (dist < 40 && dist > 10){              //Obstacle 20-60cm away from robot
        leftspeed(200);                         //LEFT always forward
        rightspeed(-280 + (8*dist));            //RIGHT will SLOW DOWN the closer it gets to an object
      }
      if (dist > 40){                           //Continue forward if no obstacle within 60cm
        leftspeed(200);               
        rightspeed(200);              
      }
      if (dist < 10){                           //Reverse at HALF SPEED if object is within 20cm
        leftspeed(-100);              
        rightspeed(-100);             
      }
    }
  } else//(codestate == false)
    {
      moveStop();
      delay(5000);
      moveForward(100);
      moveStop();
      delay(300);
      moveBackward(100);
      delay(200);
    }
    
    analogWrite(LEFT_Motor,LEFT_speed);          //Send calculated motor speed to hardware
    analogWrite(RIGHT_Motor,RIGHT_speed);    
    Serial.println(digitalRead(buttonPin));
  }

void leftspeed(int x){                          //Controller for LEFT speed and direction
  if (x>0){                                     //If x is positive, go forward
    digitalWrite(LEFT_Forward,HIGH);
    digitalWrite(LEFT_Backward,LOW);
    LEFT_speed = abs(x);
  }
  if (x<0){                                     //If x is negative, go backwards
    digitalWrite(LEFT_Backward,HIGH);
    digitalWrite(LEFT_Forward,LOW);
    LEFT_speed = abs(x);
  }
}

void rightspeed(int x){                         //Controller for RIGHT speed and direction
  if (x>0){                                     //If x is positive, go forward
    digitalWrite(RIGHT_Forward,HIGH);
    digitalWrite(RIGHT_Backward,LOW);
    RIGHT_speed = abs(x);
  }
  if (x<0){                                     //If x is negative, go backward
    digitalWrite(RIGHT_Backward,HIGH);
    digitalWrite(RIGHT_Forward,LOW);
    RIGHT_speed = abs(x);
  }
}

//Functions for pre-determined pathway stuff later on
//MAY CHANGE THE DELAY TIME DEPENDING ON TURN
void turnRight(){
  leftspeed(200);
  rightspeed(-200);
  delay(500);
}

void turnLeft(){
  leftspeed(-200);
  rightspeed(200);
  delay(500);
}

void moveForward(int cm){
  leftspeed(200);
  rightspeed(200);
  int ms = cm * 20;
  delay(ms);
}

void moveStop(){
  digitalWrite(RIGHT_Forward, LOW);
  digitalWrite(LEFT_Forward, LOW);
  digitalWrite(RIGHT_Backward, LOW);
  digitalWrite(LEFT_Backward, LOW);
  //delay(ms);
}

void moveBackward(int cm){
  leftspeed(-200);
  rightspeed(-200);
  int ms = cm * 20;
  delay(ms);
}

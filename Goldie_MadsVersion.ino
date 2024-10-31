// Motor pins
#define motor1  6                 //LEFT MOTOR
#define LEFT_Forward  4           //FORWARD LEFT
#define LEFT_Backward  5          //BACKWARD LEFT
#define motor2 9                  //RIGHT MOTOR
#define RIGHT_Forward 11          //FORWARD RIGHT 
#define RIGHT_Backward 10         //BACKWARD RIGHT

//US Sensor pins
#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// Initializing movement parameters
int dist;
int speedL = 0;
int speedR = 0;
boolean goesForward = false;
int go = 200;

void setup() {
  Serial.begin(9600);
  pinMode(motor1,OUTPUT);
  pinMode(LEFT_Forward,OUTPUT);
  pinMode(LEFT_Backward,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(RIGHT_Forward,OUTPUT);
  pinMode(RIGHT_Backward,OUTPUT);
  Serial.println("Group Project");
}

//FOR PREDETERMINED PATH
//Find whatever a 90 deg turn is 
//turnRight(), turnLeft()
//for 
void loop() {

   dist=sr04.Distance();
   Serial.println(dist);                //Print distance to Serial Monitor
  //  if (dist < 60){
  //   leftspeed(-200);
  //   rightspeed(-200 + (6*dist));
  //  }
  //  if (dist > 60){
  //   leftspeed(-200);
  //   rightspeed(-200);
  //  }
  //  Serial.println("");
  
  if (dist <= 20)
  {
    moveStop();
    delay(200);
  }

  analogWrite(motor1,speedL);
  analogWrite(motor2,speedR);
}

//Left wheel on/off
void leftspeed(int x){
  if (x<0){
  digitalWrite(LEFT_Forward,HIGH);
  digitalWrite(LEFT_Backward,LOW);
  speedL = abs(x);
  }
  if (x>0){
  digitalWrite(LEFT_Backward,HIGH);
  digitalWrite(LEFT_Forward,LOW);
  speedL = abs(x);
  }

}

//Right wheel on/off
void rightspeed(int x){
  if (x<0){
  digitalWrite(RIGHT_Forward,HIGH);
  digitalWrite(RIGHT_Backward,LOW);
  speedR = abs(x);
  }
  if (x>0){
  digitalWrite(RIGHT_Backward,HIGH);
  digitalWrite(RIGHT_Forward,LOW);
  speedR = abs(x);
  }
}

//Functions for pre-determined pathway stuff later on
//MAY CHANGE THE DELAY TIME DEPENDING ON TURN
void turnRight(){

  digitalWrite(LEFT_Forward,  HIGH);
  digitalWrite(RIGHT_Backward, HIGH);

  digitalWrite(LEFT_Backward,  LOW);
  digitalWrite(RIGHT_Foward, LOW); 

  delay(200);

  digitalWrite(LEFT_Forward,  HIGH);
  digitalWrite(RIGHT_Forward, HIGH);

  digitalWrite(LEFT_Backward,  LOW);
  digitalWrite(RIGHT_Backward, LOW); 
}

void turnLeft(){

  digitalWrite(LEFT_Backward,  HIGH);
  digitalWrite(RIGHT_Foward, HIGH);

  digitalWrite(LEFT_Forward,  LOW);
  digitalWrite(RIGHT_Backward, LOW); 

  delay(200);

  digitalWrite(LEFT_Forward,  HIGH);
  digitalWrite(RIGHT_Forward, HIGH);

  digitalWrite(LEFT_Backward,  LOW);
  digitalWrite(RIGHT_Backward, LOW); 

}

void moveForward(){
  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LEFT_Forward,  HIGH);
    digitalWrite(RIGHT_Forward, HIGH);
  
    digitalWrite(LEFT_Backward,  LOW);
    digitalWrite(RIGHT_Backward, LOW); 
  }
}

void moveStop(){
  digitalWrite(RIGHT_Forward, LOW);
  digitalWrite(LEFT_Forward, LOW);
  digitalWrite(RIGHT_Backward, LOW);
  digitalWrite(LEFT_Backward, LOW);
}

void moveBackward(){
  goesForward = false;

  digitalWrite(LEFT_Forward,  LOW);
  digitalWrite(RIGHT_Forward, LOW);

  digitalWrite(LEFT_Backward,  HIGH);
  digitalWrite(RIGHT_Backward, HIGH); 
}

#define LEFT_Motor  6   //VCC pin on Motor 1
#define LEFT_Forward  4    //Direction pin on Motor 1
#define LEFT_Backward  5    //Direction pin on Motor 1
#define RIGHT_Motor 9    //VCC pin on Motor 2
#define RIGHT_Forward 11    //Direction pin on Motor 2
#define RIGHT_Backward 10    //Direction pin on Motor 2

#include "SR04.h"   //US Sensor Library
#define TRIG_PIN 2  //US Sensor trigger pin
#define ECHO_PIN 3  //US Sensor Echo pin

#define colorpin 7
int color = 0;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);    //This is part of the US Sesor Library
long dist;                              //This variable will be used later in the void loop

int speed1 = 0; //starts the Motor 1 speed at 0
int speed2 = 0; //starts the Motor 2 speed at 0

void leftspeed(int x){        //value of leftspeed with result in the speed of the left motor with the sign changing the direction of it
  if (x>0){                   //If a positive value is imputed, the left motor will spin in the forward direction
  digitalWrite(LEFT_Forward,HIGH);
  digitalWrite(LEFT_Backward,LOW);
  speed1 = abs(x);
  }
  if (x<0){                   //If a negative value is imputed, the left motor will spin in the revirse direction
  digitalWrite(LEFT_Backward,HIGH);
  digitalWrite(LEFT_Forward,LOW);
  speed1 = abs(x);
  }

}
void rightspeed(int x){       //value of leftspeed with result in the speed of the left motor with the sign changing the direction of it
  if (x>0){                   //If a positive value is imputed, the right motor will spin in the forward direction
  digitalWrite(RIGHT_Forward,HIGH);
  digitalWrite(RIGHT_Backward,LOW);
  speed2 = abs(x);
  }
  if (x<0){                   //If a positive value is imputed, the right motor will spin in the forward direction
  digitalWrite(RIGHT_Backward,HIGH);
  digitalWrite(RIGHT_Forward,LOW);
  speed2 = abs(x);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_Motor,OUTPUT);   //defines the pins of the motors
  pinMode(LEFT_Forward,OUTPUT);
  pinMode(LEFT_Backward,OUTPUT);
  pinMode(RIGHT_Motor,OUTPUT);
  pinMode(RIGHT_Forward,OUTPUT);
  pinMode(RIGHT_Backward,OUTPUT);

  pinMode(colorpin,INPUT);  //defines the ir sensor pin
}

void loop() {
   color = digitalRead(colorpin);
   dist = sr04.Distance();          //dist will equal the distance an object is from the US Sensor in cm
   Serial.println(dist);          //prints the distance in cm
  if (color == LOW){
    leftspeed(0);
    rightspeed(0);
  }
  else{
    if (dist < 60 && dist > 20){   //if there is an object between 20 and 60 cm from the robot
      leftspeed(200);               //left motor will always go forward
      rightspeed(-280 + (8*dist));  //and the right motor will slow down the closer and closer it gets to the object resulting in the robot spinning and spinning fast as it gets closer to avoid the obstical
    }
    if (dist > 60){                //If an object is further than 60 cm from the US Sensor
      leftspeed(200);               //Left motor is forward
      rightspeed(200);              //and Right motor is forward
    }
    if (dist < 20){                //If an object is within 20 cm of the US Sensor
      leftspeed(-100);              //left motor is in reverse at half speed
      rightspeed(-100);             //and right motor is in reverse at half speed
    }
  }
  analogWrite(LEFT_Motor,speed1);     //always sets the left motor speed to whatever is calculated above
  analogWrite(RIGHT_Motor,speed2);     //always sets the right motor speed to whatever is calculated above
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

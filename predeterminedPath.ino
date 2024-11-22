#define LEFT_Motor 6                    //VCC pin on Motor 1
#define LEFT_Forward 4                  //Direction pin on Motor 1
#define LEFT_Backward 5                 //Direction pin on Motor 1
#define RIGHT_Motor 9                   //VCC pin on Motor 2
#define RIGHT_Forward 11                //Direction pin on Motor 2
#define RIGHT_Backward 10               //Direction pin on Motor 2

#include "SR04.h"                       //US Sensor declarations
#define TRIG_PIN 2  
#define ECHO_PIN 3  
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN); 

#define colorpin 7                      //IR Pin & Initialization
int color = 0;
int colorState = 0;
int onoff = 0;
bool timerRunning = false;  // Declare the timer running variable
unsigned long timerStart = 0;  // Declare the timer start time

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


}

void loop() {

moveForward(50);

turnRight();

moveForward(50);

turnRight();

moveForward(50);

turnRight();

moveForward(50);

turnRight();



  analogWrite(LEFT_Motor, LEFT_speed);          //Send calculated motor speed to hardware
  analogWrite(RIGHT_Motor, RIGHT_speed);    
}

void leftspeed(int x) {                          //Controller for LEFT speed and direction
  if (x > 0) {                                    //If x is positive, go forward
    digitalWrite(LEFT_Forward, HIGH);
    digitalWrite(LEFT_Backward, LOW);
    LEFT_speed = abs(x);
  }
  if (x < 0) {                                    //If x is negative, go backwards
    digitalWrite(LEFT_Backward, HIGH);
    digitalWrite(LEFT_Forward, LOW);
    LEFT_speed = abs(x);
  }
}

void rightspeed(int x) {                         //Controller for RIGHT speed and direction
  if (x > 0) {                                    //If x is positive, go forward
    digitalWrite(RIGHT_Forward, HIGH);
    digitalWrite(RIGHT_Backward, LOW);
    RIGHT_speed = abs(x);
  }
  if (x < 0) {                                    //If x is negative, go backward
    digitalWrite(RIGHT_Backward, HIGH);
    digitalWrite(RIGHT_Forward, LOW);
    RIGHT_speed = abs(x);
  }
}

// Functions for pre-determined pathway stuff later on
void turnRight() {
  leftspeed(200);
  rightspeed(-200);
  delay(230);
}

void turnLeft() {
  leftspeed(-200);
  rightspeed(200);
  delay(230);
}

void moveForward(int cm) {
  leftspeed(250);
  rightspeed(250);
  int ms = cm * 25;
  delay(ms);
}

void moveStop() {
  digitalWrite(RIGHT_Forward, LOW);
  digitalWrite(LEFT_Forward, LOW);
  digitalWrite(RIGHT_Backward, LOW);
  digitalWrite(LEFT_Backward, LOW);
}

void moveBackward(int cm) {
  leftspeed(-200);
  rightspeed(-200);
  int ms = cm * 25;
  delay(ms);
}

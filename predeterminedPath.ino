#define LEFT_Motor 6                    //VCC pin on Motor 1
#define LEFT_Forward 4                  //Direction pin on Motor 1
#define LEFT_Backward 5                 //Direction pin on Motor 1
#define RIGHT_Motor 9                   //VCC pin on Motor 2
#define RIGHT_Forward 11                //Direction pin on Motor 2
#define RIGHT_Backward 10               //Direction pin on Motor 2
int LEFT_speed = 0;                     //Initialize motor speeds to zero
int RIGHT_speed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_Motor, OUTPUT);          //Define motor pins
  pinMode(LEFT_Forward, OUTPUT);
  pinMode(LEFT_Backward, OUTPUT);
  pinMode(RIGHT_Motor, OUTPUT);
  pinMode(RIGHT_Forward, OUTPUT);
  pinMode(RIGHT_Backward, OUTPUT);
}

void loop() {

  moveForward(150);

  turnRight(180);

  moveForward(150);

  turnRight(180);

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
  analogWrite(LEFT_Motor, LEFT_speed);            //moves the left motor at the intended speed
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
  analogWrite(RIGHT_Motor, RIGHT_speed);          //Moves the Right Motor at the intended speed
}

void turnRight(int Degrees) {
  leftspeed(200);
  rightspeed(-200);
  delay(Degrees * 3.4);   //use 375 to get it to turn 90 degrees. Since it turns a little bit to straighten the back wheel, I am going to turn it down a bit.
  moveStop(250);
  moveForward(15);
  turnLeft(10);       //This is meant as a final adjustment and to straighted the back wheel
  moveStop(250);
}

void turnLeft(int Degrees) {
  leftspeed(-200);
  rightspeed(200);
  delay(Degrees * 3.4);
  moveStop(250);
}

void moveForward(int cm) {
  leftspeed(225);             //We found these two values from trial and error
  rightspeed(250);
  int ms = cm * 25;
  delay(ms);
  moveStop(250);
}

void moveStop(int ms_stopped) {
  digitalWrite(RIGHT_Forward, LOW);
  digitalWrite(LEFT_Forward, LOW);
  digitalWrite(RIGHT_Backward, LOW);
  digitalWrite(LEFT_Backward, LOW);
  delay(ms_stopped);
}

void moveBackward(int cm) {   //using this is not recommended because we have a stop on the back swival wheel which won't allow it to move backward straight.
  leftspeed(-200);
  rightspeed(-200);
  int ms = cm * 25;
  delay(ms);
}

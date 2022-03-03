#include <L3G.h>

#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
L3G gyro;

#define NUM_SENSORS 5
#define speed 180
#define turnSpeed 150

unsigned int lineSensorValues[NUM_SENSORS];

int calabration[NUM_SENSORS];

char control;
char input;

void calibrateSensors()
{
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);

  for(int i = 0; i < NUM_SENSORS; i++){
    calabration[i] = lineSensors.calibratedMaximumOn[i];
  }
}

void turnLeft(int degrees) {
  turnSensorReset();
  motors.setSpeeds(-turnSpeed, turnSpeed);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
  } while (angle < degrees);
  motors.setSpeeds(0, 0);
}

void turnRight(int degrees) {
  turnSensorReset();
  motors.setSpeeds(turnSpeed, -turnSpeed);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
  } while (angle > -degrees);
  motors.setSpeeds(0, 0);
}

void ManualControl(){
  input = Serial1.read();

  switch(input){
    case 'w': // forward
      Serial1.print("forward");
      motors.setSpeeds(speed,speed);
      delay(200);
      motors.setSpeeds(0,0);
      Serial1.print("stop");
      break;
    case 'a': // left
      Serial1.print("10l");
      turnLeft(10);
      break;
    case 's': // backwards
      Serial1.print("backward");
      motors.setSpeeds(speed * -1,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      Serial1.print("stop");
      break;
    case 'd': // right
      Serial1.print("10r");
      turnRight(10);
      break;
    case 'q': // 90 degrees left
      Serial1.print("90l");
      turnLeft(90);
      break;
    case 'e': // 90 degrees right
      Serial1.print("90r");
      turnRight(90);
      break;
    case 'u': // 180 degrees - u turn
      Serial1.print("u-turn");
      turnRight(180);
      break;
    case 'y':  // 360 degrees - turn
      Serial1.print("full-turn");
      turnRight(180);
      turnRight(180);
      break;
    case 'b': // Stop the zumo
      Serial1.print("stop");
      motors.setSpeeds(0,0);
      break;
    case 'm':
      Serial1.print("Manual-control");
      control = 'm';
      break;
    case 'n':
      Serial1.print("Auto-control");
      control = 'n';
      break;
  }
}

void SearchRoom(String direction){
  if(direction.equals("Right")){
    Serial1.print("90r");
    turnRight(90);
  }else if(direction.equals("Left")){
    Serial1.print("90l");
    turnLeft(90);
  }

  Serial1.print("forward");
  Serial1.print("stop");
  Serial1.print("forward");
  motors.setSpeeds(speed,speed);
  delay(400);
  motors.setSpeeds(0,0);
  Serial1.print("stop");

  // start searching
  Serial1.print("room");
  
  

  Serial1.print("backward");
  Serial1.print("stop");
  Serial1.print("backward");
  motors.setSpeeds(speed * -1,speed * -1);
  delay(400);
  motors.setSpeeds(0,0);
  Serial1.print("stop");
  
  // turns back to where it was facing
  if(direction.equals("Right")){
    Serial1.print("90l");
    turnLeft(90);
  }else if(direction.equals("Left")){
    Serial1.print("90r");
    turnRight(90);
  }
}

void AutoControl() {
  input = Serial1.read();

  switch(input){
    case 'b': // Stop the zumo 
      Serial1.print("stop");
      motors.setSpeeds(0,0);
      break; 
    case 'g':
      SearchRoom("Left");
      break;
    case 'h':
      SearchRoom("Right");
      break;
    case 'm':
      Serial1.print("Manual-control");
      control = 'm';
      break;
    case 'n':
      Serial1.print("Auto-control");
      control = 'n';
      break;  
  }
}

void setup() {
  // TODO: set up all sensors
  Serial1.begin(9600);
  lineSensors.initFiveSensors();  // inilizes 5 sensors 
  buttonA.waitForButton(); // for safety so motors dont turn until A hasnt been clicked 
  calibrateSensors(); // calabrates sensors 
  control = 'm'; // setting control to manual
  turnSensorSetup();  // setting up gyro for turning set no of degrees
  delay(500);
  turnSensorReset(); // for calibration
}

void loop() {
  turnSensorUpdate(); // start of every loop the angle is updated 
  
  switch(control){
    case 'm': 
      ManualControl();
      break;
    case 'n':
      AutoControl();
  }
}

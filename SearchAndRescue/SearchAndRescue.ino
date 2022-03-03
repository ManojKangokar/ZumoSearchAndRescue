#include <L3G.h>

#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
L3G gyro;

#define NUM_SENSORS 5
#define speed 100
#define turnSpeed 150

unsigned int lineSensorValues[NUM_SENSORS];

int calabration[NUM_SENSORS];
boolean decisionPoint;
int proxyCalibration = 5;
int lineLimit = 150;
int leftRouteCalibration;
int rightRouteCalibration;
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

  leftRouteCalibration = 0;
  rightRouteCalibration = 0;

  switch(input){
    case 'w': // forward
      Serial1.println("forward");
      motors.setSpeeds(speed,speed);
      delay(200);
      motors.setSpeeds(0,0);
      Serial1.println("stop");
      break;
    case 'a': // left
      Serial1.println("10l");
      turnLeft(10);
      break;
    case 's': // backwards
      Serial1.println("backward");
      motors.setSpeeds(speed * -1,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      Serial1.println("stop");
      break;
    case 'd': // right
      Serial1.println("10r");
      turnRight(10);
      break;
    case 'q': // 90 degrees left
      Serial1.println("90l");
      turnLeft(90);
      if(decisionPoint == true){
        decisionPoint = false;
        Serial1.println("Auto-control");
        control = 'n';
      }
      break;
    case 'e': // 90 degrees right
      Serial1.println("90r");
      turnRight(90);
      if(decisionPoint == true){
        decisionPoint = false;
        Serial1.println("Auto-control");
        control = 'n';
      }
      break;
    case 'u': // 180 degrees - u turn
      Serial1.println("u-turn");
      turnRight(180);
      break;
    case 'y':  // 360 degrees - turn
      Serial1.println("full-turn");
      turnRight(180);
      turnRight(180);
      break;
    case 'b': // Stop the zumo
      Serial1.println("stop");
      motors.setSpeeds(0,0);
      break;
    case 'm':
      Serial1.println("Manual-control");
      control = 'm';
      break;
    case 'n':
      Serial1.println("Auto-control");
      control = 'n';
      break;
    case 'g':
      SearchRoom("Left");
      break;
    case 'h':
      SearchRoom("Right");
      break;
  }
}

boolean SearchUsingProxy(){
  proxSensors.read();    
  int left_sensor = proxSensors.countsLeftWithLeftLeds();
  int center_left_sensor = proxSensors.countsFrontWithLeftLeds();
  int center_right_sensor = proxSensors.countsFrontWithRightLeds();
  int right_sensor = proxSensors.countsRightWithRightLeds();

  if(left_sensor >= proxyCalibration || center_left_sensor >= proxyCalibration || center_right_sensor >= proxyCalibration || right_sensor >= proxyCalibration){
    buzzer.playNote(NOTE_G(4), 500, 15);
    return true;
  }
  return false;
}

void SearchRoom(String direction){
  if(direction.equals("Right")){
    Serial1.println("90r");
    turnRight(90);
  }else if(direction.equals("Left")){
    Serial1.println("90l");
    turnLeft(90);
  }

  Serial1.println("forward");
  motors.setSpeeds(speed,speed);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");
  Serial1.println("forward");
  motors.setSpeeds(speed,speed);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");
  delay(200);

  // start searching
  Serial1.println("room");
  if(SearchUsingProxy() == true){ // look infront
    Serial1.println("object");
  }
  delay(200);
  turnLeft(45);
  //Serial1.println("45l");
  if(SearchUsingProxy() == true){ // look left
    Serial1.println("object");
  }
  delay(200);
  turnRight(90);
  //Serial1.println("90r"); 
  if(SearchUsingProxy() == true){ // look right
    Serial1.println("object");
  }
  turnLeft(45); // turn back to where the robot was facing
  //Serial1.println("45l");
  delay(200);
  Serial1.println("backward");
  motors.setSpeeds(speed * -1,speed * -1);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");
  Serial1.println("backward");
  motors.setSpeeds(speed * -1,speed * -1);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");
  
  // turns back to where it was facing
  if(direction.equals("Right")){
    Serial1.println("90l");
    turnLeft(90);
  }else if(direction.equals("Left")){
    Serial1.println("90r");
    turnRight(90);
  }

  // goes back to auto
  Serial1.println("Auto-control");
  control = 'n';
}

void ReachedDecisionPoint(){
  Serial1.println("backward");
  motors.setSpeeds(speed * -1,speed * -1);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");

  decisionPoint = true;
  Serial1.println("Manual-control");
  control = 'm';
}

void directionCorrection(int side){
  Serial1.println("backward");
  motors.setSpeeds(speed * -1,speed * -1);
  delay(200);
  motors.setSpeeds(0,0);
  Serial1.println("stop");
  if(side == 0){ // if left got triggered
    //Serial1.println("05r");
    turnRight(5);
  }else if(side == 1){  // if right got triggered
    //Serial1.println("05l");
    turnLeft(5);
  }
  Serial1.println("forward");
  motors.setSpeeds(speed,speed);
  delay(200);
  motors.setSpeeds(0,0);
}

void AutoControl() {
  input = Serial1.read();

  switch(input){
    case 'b': // Stop the zumo 
      Serial1.println("stop");
      motors.setSpeeds(0,0);
      Serial1.println("Manual-control");
      control = 'm';
      break; 
    case 'g':
      SearchRoom("Left");
      break;
    case 'h':
      SearchRoom("Right");
      break;
    case 'm':
      Serial1.println("Manual-control");
      control = 'm';
      break;
    case 'n':
      Serial1.println("Auto-control");
      control = 'n';
      break;  
  }
  // all line sensors get hit
  lineSensors.read(lineSensorValues);
  if((lineSensorValues[0] >= lineLimit)  && (lineSensorValues[4] >= lineLimit)){
    Serial1.println("corner-hit");
    motors.setSpeeds(0,0);
    ReachedDecisionPoint();
  }else if(lineSensorValues[0] >= lineLimit){ // left line sensors get hit
    motors.setSpeeds(0,0);
    directionCorrection(0);
  }else if(lineSensorValues[4] >= lineLimit){  // right line sensors get hit
    motors.setSpeeds(0,0);
    directionCorrection(1);
  }else{  // else go forward 
    Serial1.println("forward");
    motors.setSpeeds(speed,speed);
    delay(200);
    motors.setSpeeds(0,0);
  }
}

void setup() {
  // set up all sensors
  decisionPoint = false;
  Serial1.begin(9600);
  lineSensors.initFiveSensors();  // inilizes 5 sensors 
  buttonA.waitForButton(); // for safety so motors dont turn until A hasnt been clicked 
  proxSensors.initThreeSensors();
  //calibrateSensors(); // calabrates sensors 
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

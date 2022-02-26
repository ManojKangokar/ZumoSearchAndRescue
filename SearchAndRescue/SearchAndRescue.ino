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
      motors.setSpeeds(speed,speed);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 'a': // left
      motors.setSpeeds(speed * -1,speed);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 's': // backwards
      motors.setSpeeds(speed * -1,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 'd': // right
      motors.setSpeeds(speed,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 'q': // 90 degrees left
      turnLeft(90);
      break;
    case 'e': // 90 degrees right
      turnRight(90);
      break;
    case 'u': // 180 degrees - u turn
      turnRight(180);
      break;
    case 'y':  // 360 degrees - turn
      turnRight(360);
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
    Serial1.print("Manual Control");
    break;
  }
}

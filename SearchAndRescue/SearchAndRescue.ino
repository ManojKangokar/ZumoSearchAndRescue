#include <Wire.h>
#include <Zumo32U4.h>
const uint16_t maxSpeed = 400;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
#define speed 150

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

void ManualControl(){
  input = Serial1.read();

  switch(input){
    case 'w':
      motors.setSpeeds(speed,speed);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 'a':
      motors.setSpeeds(speed * -1,speed);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 's':
      motors.setSpeeds(speed * -1,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      break;
    case 'd':
      motors.setSpeeds(speed,speed * -1);
      delay(200);
      motors.setSpeeds(0,0);
      break;
  }
}

void setup() {
  Serial1.begin(9600);
  lineSensors.initFiveSensors();  // inilizes 5 sensors 
  buttonA.waitForButton(); // for safety so motors dont turn until A hasnt been clicked 
  calibrateSensors(); // calabrates sensors 
  control = 'm'; // setting control to manual

  // make sure you set up all sensors 
}

void loop() {
  switch(control){
    case 'm': 
    ManualControl();
    Serial1.print("Manual Control");
    break;
  }
}

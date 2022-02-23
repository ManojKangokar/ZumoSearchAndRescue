#include <Wire.h>
#include <Zumo32U4.h>
const uint16_t maxSpeed = 400;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

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
}

void setup() {
  lineSensors.initFiveSensors();
  buttonA.waitForButton();
  calibrateSensors();
  delay(1000);
}

void Manual(char check){

  
switch(check){
  case 'w':
for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  break;
  case 'a':
for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed * -1);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed * -1);
    motors.setRightSpeed(speed);
    delay(2);
  }
  break;
  case 's':
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed * -1);
    motors.setRightSpeed(speed * -1);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed * -1);
    motors.setRightSpeed(speed * -1);
    delay(2);
  }
  break;
  case'd':
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed * -1);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed * -1);
    delay(2);
  }
  break;
}
  
}


void autoControl(){
  int16_t position = lineSensors.readLine(lineSensorValues);
  
  //lineSensorValues[i];

  while(lineSensorValues[0] !> 40){
    // keep turning left
  }

  while(lineSensorValues[4] !> 40){
    // keep turning right
  }

  // use this to calculate centre 
}


void loop() {
  String input;

  if(Serial.available()){
    input = Serial.readString();
    Serial.print("I recieved: ");
    Serial.print(input);
  }

char check = input[0];

if(check.equals("m")){
  Manual(check);
}
if(check.equals("p")){
  Manual(check);
}


delay(500);
}

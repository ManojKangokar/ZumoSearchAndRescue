#include <Wire.h>
#include <Zumo32U4.h>
const uint16_t maxSpeed = 400;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;


#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

void calibrateSensors()
{

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
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


}

void loop() {
  int16_t position = lineSensors.readLine(lineSensorValues);

  for(int i = 0; i < NUM_SENSORS; i++){
    Serial.print("line ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(lineSensorValues[i]);
     Serial.println();
  }
   Serial.println();
}

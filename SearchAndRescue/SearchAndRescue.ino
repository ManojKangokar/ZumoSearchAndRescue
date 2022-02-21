#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

void setup() {
  buttonA.waitForButton();

  delay(1000);
}

void loop() {
  String input;

  if(Serial.available()){
    input = Serial.readString();
    Serial.print("I recieved: ");
    Serial.print(input);
  }

char check = input[0];

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
delay(500);
}

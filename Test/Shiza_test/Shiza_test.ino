//#include <ESP8266WiFi.h>
#include "GyverMotor.h"

class MotorSetup {
public:
  // Константы, пины, прочее
  const int MOTOR_L1 = D5;
  const int MOTOR_L2 = D6;
  const int MOTOR_R1 = D7;
  const int MOTOR_R2 = D8;
};

// Объявляем моторы
//int dir;
MotorSetup motorSetup;
GMotor motorL(DRIVER2WIRE, motorSetup.MOTOR_L1, motorSetup.MOTOR_L2, LOW);
GMotor motorR(DRIVER2WIRE, motorSetup.MOTOR_R1, motorSetup.MOTOR_R2, LOW);


void setup() {
  Serial.begin(115200);
  delay(10);

  // Подготавливаем моторы
  motorL.setMode(STOP);
  motorL.setSpeed(255);
  motorR.setMode(STOP);
  motorL.setSpeed(255);
}

void loop() {
  MoveForward();
  delay(2000);
  MoveStop();
  delay(1000);
  MoveRight();
  delay(3000);
  MoveLeft();
  delay(2000);
  MoveBack();
}



void MoveForward() {
  motorL.setMode(FORWARD);
  motorR.setMode(FORWARD);
}

void MoveStop() {
  motorL.setMode(STOP);
  motorR.setMode(STOP);
}

void MoveBack() {
  motorL.setMode(BACKWARD);
  motorR.setMode(BACKWARD);
}

void MoveLeft() {
  motorL.setMode(BACKWARD);
  motorR.setMode(FORWARD);
}

void MoveRight() {
  motorL.setMode(FORWARD);
  motorR.setMode(BACKWARD);
}
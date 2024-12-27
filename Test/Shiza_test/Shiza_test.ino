//#include <ESP8266WiFi.h>
#include "GyverMotor.h"

class MotorSetup {
public:
  // Константы, пины, прочее
  // const int MOTOR_L1 = D5;
  // const int MOTOR_L2 = D6;
  // const int MOTOR_R1 = D3;
  // const int MOTOR_R2 = D4;

  const int MOTOR_L1 = D0;
  const int MOTOR_L2 = D7;
  const int MOTOR_R1 = D5;
  const int MOTOR_R2 = D6;
};

// Объявляем моторы
MotorSetup motorSetup;
GMotor motorL(DRIVER2WIRE, motorSetup.MOTOR_L1, motorSetup.MOTOR_L2, LOW);
GMotor motorR(DRIVER2WIRE, motorSetup.MOTOR_R1, motorSetup.MOTOR_R2, 0);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(2, OUTPUT);

  // Подготавливаем моторы
  // motorL.setMode(STOP);
  // motorL.setSpeed(255);
  // motorR.setMode(STOP);
  // motorL.setSpeed(255);
}

void loop() {
  MoveForward(); //!
  digitalWrite(2, 0);
  delay(3000);

  MoveRight();
  digitalWrite(2, 1);
  delay(3000);

  MoveLeft(); //!
  digitalWrite(2, 0);
  delay(3000);

  MoveBack();
  digitalWrite(2, 1);
  delay(3000);
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
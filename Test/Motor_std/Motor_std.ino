#include <ESP8266WiFi.h>
#include "GyverMotor.h"

class MotorSetup 
{
  public:
    // Константы, пины, прочее
};


// Создаём объект сервера
WiFiServer server(port);

// Объявляем моторы
const int MOTOR_L1 = D5;
const int MOTOR_L2 = D6;
const int MOTOR_R1 = D7;
const int MOTOR_R2 = D8;
int dir;

MotorSetup motorSetup;
GMotor motorL(DRIVER2WIRE, MOTOR_L1, MOTOR_L2, LOW);
GMotor motorR(DRIVER2WIRE, MOTOR_R1, MOTOR_R2, LOW);


void setup() {
  WiFi.persistent(false);
  Serial.begin(115200);
  delay(10);

  // Подготавливаем светодиод (синий)
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  /*pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);*/
  
  // Подготавливаем моторы
  motorL.setMode(STOP);
  motorL.setSpeed(255);
  motorR.setMode(STOP);
  motorL.setSpeed(255);


void loop() {

    MoveForward();
    delay(2000);
    MoveStop();
    delay(1000);
    MoveRight();
    delay(3000);
    MoveLight();
    delay(2000);
    MoveBack();

  }



void MoveForward()
{
  motorL.setMode(FORWARD);
  motorR.setMode(FORWARD);
}

void MoveStop()
{
  motorL.setMode(STOP);
  motorR.setMode(STOP);
}

void MoveBack()
{
  motorL.setMode(BACKWARD);
  motorR.setMode(BACKWARD);
}

void MoveLeft()
{
  motorL.setMode(BACKWARD);
  motorR.setMode(FORWARD);
}

void MoveRight()
{
  motorL.setMode(FORWARD);
  motorR.setMode(BACKWARD);
}
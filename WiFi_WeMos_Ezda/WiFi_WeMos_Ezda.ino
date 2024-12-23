/* 
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 */
#include <ESP8266WiFi.h>
#include "GyverMotor.h"

const char* ssid = "Timur's WiFi";
const char* password = "Password";
const int port = 80;

// Создаём объект сервера
WiFiServer server(port);

// Объявляем моторы
const int MOTOR_L1 = D5;
const int MOTOR_L2 = D6;
const int MOTOR_R1 = D7;
const int MOTOR_R2 = D8;
int dir;

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

  // WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Запускаем сервер
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP()); // Вывод IP
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Считываем запрос
  int val;
  // Направление езды
  /*if (req.indexOf("/gpio/0") != -1) // Устаревшее
    {
      val = 0;
      MoveStop();
    }
  else if (req.indexOf("/gpio/1") != -1) // Устаревшее
    {
      val = 1;
      MoveForward();
    } */


  //IN PROCESS
  if (req.indexOf("f") != -1) 
  {
    val = 0;
    dir = 1;
  }

  else if (req.indexOf("s") != -1) 
  {
    val = 0;
    dir = 0;
  }

  else if (req.indexOf("r") != -1) 
  {
    val = 1;
    dir = 2;
  }

  else if (req.indexOf("l") != -1) 
  {
    val = 1;
    dir = 3;
  }

  else if (req.indexOf("b") != -1) 
  {
    val = 0;
    dir = 4;
  }

  else 
  {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Едем исходя из направления движения
  switch(dir)
  {
    case 1: MoveForward(); break;
    case 4: MoveBack(); break;
    case 2: MoveRight(); break;
    case 3: MoveLeft(); break;
    default: MoveStop(); break;
  }


  // Редактируем состояние светодиода
  digitalWrite(2, val);
  client.flush(); // ???

  // Собираем ответ пользователю
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\GPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";
  String js = "HTTP/1.1 200 OK\r\nContent-Type: text/javascript\r\n\r\nalert('TEST')";

  // Отправляем ответ
  client.print(s);
  client.print(js);
  delay(1);
  Serial.println("Client disonnected");
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
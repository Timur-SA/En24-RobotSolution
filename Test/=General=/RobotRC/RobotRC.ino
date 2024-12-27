//#include <ESP8266WiFi.h>
#include <GyverMotor.h>

class MotorSetup {
public:
  const int MOTOR_L1 = D0;
  const int MOTOR_L2 = D7;
  const int MOTOR_R1 = D5;
  const int MOTOR_R2 = D6;
};

class WiFiSetup {
public:
  const char* NAME = "Timur's WiFi";
  const char* PASS = "Password";
  const int PORT = 80;

  void StatsShow() {
    Serial.println("WiFi is Ready!");
    Serial.print("SSID: ");
    Serial.println(NAME);

    Serial.print("Pass: ");
    Serial.println(PASS);

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }

  void RequestRead() {
  }
};

// Подготавливаем объекты
WiFiSetup wifiSetup;
MotorSetup MS;
GMotor motorL(DRIVER2WIRE, MS.MOTOR_L1, MS.MOTOR_L2, LOW);
GMotor motorR(DRIVER2WIRE, MS.MOTOR_R1, MS.MOTOR_R2, LOW);
WiFiServer server(wifiSetup.PORT);


void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(2, OUTPUT);

  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  wifiSetup.StatsShow();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  String req = client.readStringUntil('\r');

  if(req == "f")
  {
    MoveForward();
  }

  else if(req == "b")
  {
    MoveBack();
  }

  else if(req == "r")
  {
    MoveRight();
  }

  else if(req == "l")
  {
    MoveLeft();
  }

  else
  {
    MoveStop();
  }
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
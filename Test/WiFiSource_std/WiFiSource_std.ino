// Стандартный IP:
// 192.168.4.1
#include <ESP8266WiFi.h>

class WiFiSetup
{
  public: 
   const char* NAME = "ESP8266 - Tuapse";
   const char* PASS = "LifeInWater";
   const int PORT = 80;

    void StatsShow()
    {
      Serial.println("WiFi is Ready!");
      Serial.print("SSID: ");
      Serial.println(NAME);

      Serial.print("Pass: ");
      Serial.println(PASS);

      Serial.print("IP: ");
      Serial.println(WiFi.softAPIP());
    }

    void RequestRead()
    {

    }
};

// Подготавливаем объекты
WiFiSetup wifiSetup;
WiFiServer server(wifiSetup.PORT);

void setup() {
  // Подготавливаем AP
  Serial.begin(115200);
  Serial.println("===PROGRAMM STARTED!===");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifiSetup.NAME, wifiSetup.PASS);
  wifiSetup.StatsShow();
  

  // Готовим Пины
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
}


void loop() 
{ 
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if(req == "1")
  {
    digitalWrite(D4, 0);
    delay(1000);
    digitalWrite(D4, 1);
  }
  else if (req == "2")
  {
    digitalWrite(D4, 0);
    delay(250);
    digitalWrite(D4, 1);
    delay(250);
    digitalWrite(D4, 0);
    delay(250);
    digitalWrite(D4, 1);
  }

  else
  {
    digitalWrite(D4, 0);
  }

  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\ OK!");
}
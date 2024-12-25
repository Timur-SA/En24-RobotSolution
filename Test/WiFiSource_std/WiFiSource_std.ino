// Стандартный IP:
// 192.168.4.1
#include <ESP8266WiFi.h>

class WiFiSetup
{
  public: 
   const char* NAME = "ESP8266 - Tuapse";
   const char* PASS = "LifeInWater";
};

// Подготавливаем объекты
WiFiSetup wifiSetup;


void setup() {
  // Подготавливаем точку доступа
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifiSetup.NAME, wifiSetup.PASS);
  Serial.println()

}

void loop() 
{

}
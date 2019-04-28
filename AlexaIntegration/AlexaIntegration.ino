#include "ESP8266WiFi.h"
#include "WiFiManager.h"
#include "fauxmoESP.h"


fauxmoESP homeDevice;
uint8_t relay =14;
WiFiClient espClient;
#define switch  "light"

void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.begin(115200);
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("LightingPLC");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  homeDevice.createServer(true); 
  homeDevice.setPort(80);
  
  homeDevice.enable(true);
  homeDevice.addDevice(switch);
  homeDevice.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value)
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if (strcmp(device_name, switch) == 0)
    {
      Serial.println("RELAY 1 switched by Alexa");
      if(state){
      digitalWrite(relay, LOW);
    }else{
      digitalWrite(relay, HIGH);
    }
    }
  });
 
}

void loop()
{
  homeDevice.handle();
}

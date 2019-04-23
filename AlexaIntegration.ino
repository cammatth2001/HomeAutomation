#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "WiFiManager.h"
#include "DNSServer.h"
#include "fauxmoESP.h"
//#include "credentials.h"

fauxmoESP homeDevice;
uint8_t relay =14;

ESP8266WebServer server;
DNSServer dnsServer;
WiFiClient espClient;

#define pin_relay  "Kitchen Light"



void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  Serial.begin(115200);
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("LightingPLC");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  homeDevice.createServer(true); 
  homeDevice.setPort(80);
  server.on("/", handleRoot);
  server.on("/toggle", toggleRelay);
  server.begin();
  homeDevice.enable(true);
  homeDevice.addDevice(pin_relay);
  homeDevice.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value)
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if (strcmp(device_name, pin_relay) == 0)
    {
      digitalWrite(relay, state ? HIGH : LOW);
    }
  });
}

void loop()
{
  homeDevice.handle();
  server.handleClient();
}
void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  digitalWrite(relay, !digitalRead(relay));
  server.send(200, "text/html", "<form action=\"/toggle\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}
void toggleRelay()  //the toggle function to turn the relay on and off
{
    digitalWrite(relay, !digitalRead(relay));
    server.send(204, "");
}

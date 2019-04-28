#include <ESP8266mDNS.h>
#include "ESP8266WebServer.h"
#include "DNSServer.h"
#include "ESP8266WiFi.h"
#include "WiFiManager.h"

ESP8266WebServer server; //creating a server object
DNSServer dnsServer;
uint8_t relay =14;

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
  server.on("/", handleRoot);
  server.on("/toggle", toggleRelay);
  server.begin();
   if (!MDNS.begin("esp8266")) 
      {             // Start the mDNS responder for esp8266.local
        Serial.println("Error setting up MDNS responder!");
      }
    Serial.println("mDNS responder started");
}

void loop()
{
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
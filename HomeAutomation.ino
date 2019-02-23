//Setting up an ESP8266 to toggle on and off a pin based on the /toggle being input into the web browser

#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "WiFiManager.h"
#include "DNSServer.h"
#include <ESP8266mDNS.h>
uint8_t pin_relay =14; //assigning pin 16 to the variable pin_led
ESP8266WebServer server; //creating a server object
DNSServer dnsServer;
void setup()
{  
    pinMode(pin_relay, OUTPUT);  //setting the assigned pin as an output
    Serial.begin(115200);  //setting the serial port baud rate
    WiFiManager wifiManager;
 //   wifiManager.resetSettings();  //resets the settings as it will autoconnect to last known good settings
    wifiManager.autoConnect("LightingPLC");
    Serial.print("IP Address: "); //prints the ip assigned by the router to the serial monitor
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.subnetMask());
    if (!MDNS.begin("esp8266")) 
      {             // Start the mDNS responder for esp8266.local
        Serial.println("Error setting up MDNS responder!");
      }
    Serial.println("mDNS responder started");
   // server.on("/",[](){server.send(200,"text/plain","I control the relay");});
    server.on("/", handleRoot);
    server.on("/toggle", toggleRelay);
    server.begin();  //starts the server process
}

void loop()
{
  dnsServer.processNextRequest();
  server.handleClient();
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  digitalWrite(pin_relay, !digitalRead(pin_relay));
  server.send(200, "text/html", "<form action=\"/toggle\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
  //server.sendHeader("Location","127.0.0.1");
  //server.send(303); 
 // server.send(204, "");
}
void toggleRelay()  //the toggle function to turn the relay on and off
{
    digitalWrite(pin_relay, !digitalRead(pin_relay));
    server.send(204, "");
    //server.sendHeader("Location","127.0.0.1");
   // server.send(303); 
}

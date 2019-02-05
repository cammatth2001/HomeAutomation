//Setting up an ESP8266 to toggle on and off a pin based on the /toggle being input into the web browser

#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

uint8_t pin_relay = ; //assigning pin 16 to the variable pin_led

char* ssid = ""; //setting up the ssid and wifi password
char* password = "";


ESP8266WebServer server; //creating a server object

void setup()
{
    pinMode(pin_relay, OUTPUT);  //setting the assigned pin as an output
    WiFi.begin(ssid, password);
    Serial.begin(115200);  //setting the serial port baud rate
    
    while(WiFi.status()!=WL_CONNECTED)
    {
    delay(500);  //setting a delay while the wifi is being setup
    Serial.println("");
    Serial.println("IP Address: "); //prints the ip assigned by the router to the serial monitor
    Serial.println("Wifi.localIP()");
    }
    
    server.on("/",[](){server.send(200,"text/plain","I control the relay");});
    server.on("/toggle",toggleRelay);
    server.begin();  //starts the server process
}

void loop()
{
  server.handleClient();
}

void toggleRelay()  //the toggle function to turn the relay on and off
{
    digitalWrite(pin_relay, !digitalRead(pin_relay));
    server.send(204, "");
}

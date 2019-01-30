#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "WiFly.h"
#include <dht.h>
#define SSID      "RIOTU"
#define KEY       "ccis2010"
// WIFLY_AUTH_OPEN / WIFLY_AUTH_WPA1 / WIFLY_AUTH_WPA1_2 / WIFLY_AUTH_WPA2_PSK
#define AUTH      WIFLY_AUTH_WPA2_PSK
#define dht_apin A0 // Analog Pin sensor is connected to
#define UDP_HOST_IP        "255.255.255.255"      // broadcast
#define UDP_REMOTE_PORT    8080
#define UDP_LOCAL_PORT     8080

dht DHT;

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(uart);

void setupUDP(const char *host_ip, uint16_t remote_port, uint16_t local_port)
{
  char cmd[32];
  
  wifly.sendCommand("set w j 1\r", "AOK");   // enable auto join
  
  wifly.sendCommand("set i p 1\r", "AOK");
  snprintf(cmd, sizeof(cmd), "set i h %s\r", host_ip);
  wifly.sendCommand(cmd, "AOK");
  snprintf(cmd, sizeof(cmd), "set i r %d\r", remote_port);
  wifly.sendCommand(cmd, "AOK");
  snprintf(cmd, sizeof(cmd), "set i l %d\r", local_port);
  wifly.sendCommand(cmd, "AOK");
  wifly.sendCommand("save\r");
  wifly.sendCommand("reboot\r");
}

void setup() {

  Serial.begin(9600);
  Serial.println("--------- WIFLY UDP --------");
  
  uart.begin(9600);     // WiFly UART Baud Rate: 9600
  wifly.reset();
  
  while (1) {
    Serial.println("Try to join " SSID );
    if (wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Succeed to join " SSID);
      wifly.clear();
      break;
    } else {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 1 second and try again...");
      delay(1000);
    }
  }
    
  
  setupUDP(UDP_HOST_IP, UDP_REMOTE_PORT, UDP_REMOTE_PORT);
  
  delay(1000);
  wifly.clear();
}

unsigned int time_point = 0;

StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void loop() {
    DHT.read11(dht_apin);
    root["h"] = DHT.humidity;
    root["t"] = DHT.temperature;
    root.printTo(wifly);
delay(2500);
}

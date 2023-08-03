#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiManager.h>

void setup_wifi(boolean reset = false) {
  // WiFiManager setup function to dynamically connect to WiFi and saving credentials in EEEPROM for future use
  WiFiManager wifiManager;

  // reset WiFiManager settings 
  if(reset){
    wifiManager.resetSettings();
  }

  wifiManager.autoConnect("pc-switch-AP");

  // Connected to WiFi
  Serial.println("Connected.");
}

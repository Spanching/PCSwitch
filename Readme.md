# PC Switch

## 1. Motivation

This repository shows my effort to be able to control an RC Socket and my PC with MQTT/Alexa. It is highly recommendet to have a look at my [RC Socket repository](http://test.com) to understand the usage.

## 2. Hardware

- Wemos D1 mini
- Photoresistor
- LED (white works best)
- perf board with some male/female header pins

At a point in the future, I want to add my board and schematic files from eagle. Right now I an just going to explain what I did. I connected 5V and GND of an unused USB Connector on my Motherboard to the Wemos. Then I added the Photoresistor in parallel with the Power Switch of my PC. This is needed that my PC can be turned on and off from MQTT and via the switch on the case. Lastly I built a voltage divider using 5K and 10K Ohm resistors to decrease the voltage of the Power LED from 5V to 3.2 for the Analog Pin of my Wemos D1 mini. This is needed to measure if the PC is still running when turned off, otherwise my RC switch socked would be turned off while Windows installs updates. And we all know Windows really does not like that.

## 3. Installation

For this to work you will need the following Arduino Libraries:
- Arduino
- PubSubClient
- WiFiClient
- ESP8266WiFi
- WiFiManager
- ArduinoOTA
- RCSwitch

All of which are available in the Arduino IDE.

## 4. Usage

I built this device into my PC and use Node-Red to send the corresponding MQTT messages. I have two topics for power (home/bedroom/ultrazaziki/power) and for my RC Socket (home/bedroom/rcsocket). Those are mapped to the corresponding Inputs with Node-Red. For Example, I am using it with Alexa and other MQTT messages.
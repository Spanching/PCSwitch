# PC Switch

## Motivation

This repository shows my effort to be able to control my pc with MQTT/Alexa.

## Hardware

- Wemos D1 mini
- photoresistor
- LED (white works best)
- perfboard with some male/female header pins (Wemos D1 mini shield works best)
- 5K/10K Ohm resistor

At a point in the future, I want to add my board and schematic files from eagle. Right now I an just going to explain what I did. I connected 5V and GND of an unused USB Connector on my Motherboard to the Wemos. Then I added the photoresistor in parallel with the Power Switch of my PC. This is needed that my PC can be turned on and off from MQTT and via the switch on the case. Lastly I built a voltage divider using 5K and 10K Ohm resistors to decrease the voltage of the Power LED from 5V to 3.2 for the Analog Pin of my Wemos D1 mini. This is needed to measure if the PC is still running when turning off, because I also want to control an RC Socket behind my PC to turn off the power completely, which should only be done when the PC is completely turned off as the power should not be cut during Windows updates.

## Installation

For this to work you will need the following Arduino Libraries:
- Arduino
- PubSubClient
- WiFiClient
- ESP8266WiFi
- WiFiManager
- ArduinoOTA

All of which are available in the Arduino IDE.

Copy ```config_sample.h``` to ```config.h``` and input your username, password and server-ip for your MQTT broker.

## 3D Printed case

You can find the .stl files for the case I printed on Thingiverse. I included the Fusion 360 file as an easy way to change the design. Currently, it only works with a Wemos D1 mini shield or custom PCB fitted very closely to the size of the microcontroller.

## Connection to your PC

First, in this section, I have to put a disclaimer, that you should *never* do this if you don't know what you are doing! Once you open your pc up, often you will lose your warranty. Also, *never* work on your pc while it is running, you can damage parts or harm yourself. I am not responsible for anything that happens while you are working on your pc, so proceed at your own risk.

If you want to go on anyway, here is how to connect the device to your pc:

PICTURE HERE

## Integration into HomeAssistant

If you want to integrate this device into HomeAssistant, you can add the following lines to your ```configuration.yaml```:

```yaml
mqtt:
  switch:
    - command_topic: "ultrazaziki/power"
      state_topic: "ultrazaziki/status"
      name: "PC"
      payload_on: "1"
      payload_off: "0"
      state_on: "1"
      state_off: "0"
      optimistic: false
```

The configuration should speak for itself, but the ```opimistic``` parameter allows that the configured switch in HomeAssistant will only turn off when the pc is shut down completely, which allows for a lot more automations and is needed to control a smart socket, otherwise the power could be cut from your running pc.

## Examples

Here I want to give you some examples for automations that could be useful with this device:

- Automatically turning on/off a smart socket to your pc: If the status of your pc turns from on to off, you can also switch off the socket to remove power from your pc. Likewise, if the socket turns on (after a short delay) you can turn on your pc, so it is never powered if it is not turned on.
- Set predefined light scene/play a defined playlist/etc. when your pc turns on to make it easier to concentrate right in the beginning and set the right mood for working

All those automations can be set up using Node-Red or like me HomeAssistant.
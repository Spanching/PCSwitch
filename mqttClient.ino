#include <PubSubClient.h>
#include <WiFiClient.h>
#include "config.h"

bool readPCStillAlive();
float readPCStillAliveValue();
void togglePC();

WiFiClient espClient;

PubSubClient client(espClient);

char* topic_power = "ultrazaziki/power";
char* topic_status = "ultrazaziki/status";

char* username = MQTT_USER;
char* password = MQTT_PASSWORD;

bool last_alive = false;
bool alive = false;

unsigned long last_millis_5s = 0;
unsigned long last_millis_5m = 0;
unsigned long last_millis_reconnect = 0;

unsigned long mills = 0;

void setup_mqtt(){
  // setup function to connect to the MQTT Server defined in config.h
  char * server = (char *) malloc(32);
  server = MQTT_SERVER;                       // cast from bytes to char*
  client.setServer(server, 1883);
  client.setCallback(callback);
  Serial.print("Setup Mqtt with server ");
  Serial.println(server);
}

void loop_mqtt(){
  if (!client.connected()) {
    reconnect();
  }
  mills = millis();
  // we don't have to handle overflow because the result of unsigned longs overflows as well
  // around every 50 days, the update inverval goes from 5 seconds to maximum 10 seconds once
  // which does not affect it at all 
  if (mills - last_millis_5s >= 5000) {
    // reads status every 5 seconds
    last_millis_5s = mills;
    last_alive = alive;
    alive = readPCStillAlive();
    // no overflow handling as well for the same reason as above, it might take 10 minutes for one 
    // update approximately every 50 days
    if (mills - last_millis_5m >= 300000) {
      // publish status every 5 minutes
      last_millis_5m = mills;
      client.publish(topic_status, (alive)? "1" : "0");
    } else if (last_alive != alive) {
      // publish status if changed by mqtt command
      client.publish(topic_status, (alive)? "1" : "0");
    }
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int param_length) {
  // print incoming messages
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String str_payload = "";
  for (int i = 0; i < param_length; i++) {
    Serial.print((char)payload[i]);
    str_payload += (char)payload[i]; 
  }
  Serial.println();

  last_alive = alive;
  alive = readPCStillAlive();
  if (strcmp(topic, topic_power) == 0){
    if (str_payload.toInt() == 1 && !alive) {
      // turn on pc if 1 was sent on topic and pc is not already powered
      Serial.println("PC on");
      togglePC();
    } else if(str_payload.toInt() == 0 && alive) {
      // turn off pc if 0 was sent on topic and pc is already powered
      Serial.println("PC off");
      togglePC();
    }
    // always publish status after receiving any mqtt command
    alive = readPCStillAlive();
    client.publish(topic_status, (alive)? "1" : "0");
  }
}

void reconnect() {
  // reconnecting to MQTT server after losing connection
  if (!client.connected()) {
    if (millis() - last_millis_reconnect < 5000) {
      // only try reconnect every 5 seconds
      return;
    }
    last_millis_reconnect = millis();

    Serial.print("Attempting MQTT connection...");
    String clientId = "PCSwitch-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), username, password)) {
      // connection successful, subscribe to power topic
      Serial.println("MQTT connected!");
      client.subscribe(topic_power);
    } else {
      // connection failed, retry after 5 seconds
      Serial.println(" failed, trying again in 5 seconds");
    }
  }
}

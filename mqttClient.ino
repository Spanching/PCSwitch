#include <PubSubClient.h>
#include <WiFiClient.h>
#include "config.h"

bool readPCStillAlive();
float readPCStillAliveValue();
void togglePC();

WiFiClient espClient;

PubSubClient client(espClient);

char* topic_pc = "home/bedroom/ultrazaziki/power";
char* topic_pc_alive_value = "home/bedroom/ultrazaziki/alive/value";
char* topic_rcsocket = "home/bedroom/rcsocket";

char* username = MQTT_USER;
char* password = MQTT_PASSWORD;

void setup_mqtt(){
  char * server = (char *) malloc(32);
  server = "192.168.0.20";
  client.setServer(server, 1883);
  client.setCallback(callback);
  Serial.print("Setup Mqtt with server");
  Serial.println(server);
}

void loop_mqtt(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int param_length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String str_payload = "";
  for (int i = 0; i < param_length; i++) {
    Serial.print((char)payload[i]);
    str_payload += (char)payload[i]; 
  }
  Serial.println();
  
  if (strcmp(topic, topic_pc)==0){
    if (str_payload.toInt() == 1) {
      Serial.println("PC on");
      togglePC();
    } else if(str_payload.toInt() == 0) {
      Serial.println("PC off");
      togglePC();
      while(readPCStillAlive()) ;
      delay(1000);
      // send RCSocket to turn off
      client.publish(topic_rcsocket, "0");
    }
  }
  
  if (strcmp(topic, topic_pc_alive_value)==0){
    str_payload = String(readPCStillAliveValue());
  }
  
  char* tmp = (char*)malloc(5+1);
  char* back_topic = (char*)malloc(200);
  memset(back_topic, '\0', 200);
  strcpy(back_topic, topic);
  strcat(back_topic, "/back");
  Serial.print(back_topic);
  Serial.println(":  " + str_payload);
  str_payload.toCharArray(tmp, 5+1);
  client.publish(back_topic, tmp);
  free(tmp);
  free(back_topic);
}

void reconnect() {
  // Loop until we're re-/connected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), username, password)) {
      Serial.println("MQTT connected");
      client.subscribe(topic_pc);
      client.subscribe(topic_pc_alive_value);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in a couple seconds");
      // Wait 5 seconds before retrying
      delay(2500);
    }
  }
}

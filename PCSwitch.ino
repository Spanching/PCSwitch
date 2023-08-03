
void setup_mqtt();
void setup_wifi(boolean reset = false);
void setup_ota();
void loop_ota();
void loop_mqtt();
bool readPCStillAlive();
void setupPC();

void setup() {
  Serial.begin(115200);
  // disable the D1 minis led, as it is incased and not visible
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  
  // setup all parts of the PC Switch
  setup_wifi();
  setup_mqtt();
  setup_ota();
  setupPC();
}

void loop() {
  // loop for OTA Updates and receiving MQTT commands
  loop_ota();
  loop_mqtt();
}

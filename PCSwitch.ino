void setup_mqtt();
void setup_wifi(boolean reset);
void setup_ota();
void loop_ota();
void loop_mqtt();
bool readPCStillAlive();

void setup() {
  Serial.begin(115200);
  setup_wifi(false);
  setup_mqtt();
  setup_ota();
  setupPC();
}

void loop() {
  loop_ota();
  loop_mqtt();
}

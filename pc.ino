#define PC_START_PIN D6
#define PC_ALIVE_PIN A0

void setupPC() {
  // setup all pins for status and powering on/off the pc
  pinMode(PC_START_PIN, OUTPUT);
  digitalWrite(PC_START_PIN, LOW);
  pinMode(PC_ALIVE_PIN, INPUT);
}

void togglePC() {
  // simulates pressing the pc's power button for 0.5 seconds
  digitalWrite(PC_START_PIN, HIGH);
  delay(500);
  digitalWrite(PC_START_PIN, LOW);
  Serial.println("PC toggled");
}

bool readPCStillAlive() {
  // returns turue if pc is powered on, if power LED on the pc is turned on
  // the analog input will read less than 1024 (testing showed a value of about 600)
  // if power LED is off, the value will be 1024
  float average = 0.0;
  for (int i = 0; i < 10; i++) {
    average += analogRead(PC_ALIVE_PIN);  
  }
  average = average / 10;
  return (average < 800);
}
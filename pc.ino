#define PC_START_PIN D1
#define PC_ALIVE_PIN A0

void setupPC() {
  pinMode(PC_START_PIN, OUTPUT);
  digitalWrite(PC_START_PIN, LOW);
  pinMode(PC_ALIVE_PIN, INPUT);
}

void togglePC() {
  digitalWrite(PC_START_PIN, HIGH);
  delay(500);
  digitalWrite(PC_START_PIN, LOW);
  Serial.println("PC toggled");
}

bool readPCStillAlive() {
  float average = 0.0;
  for (int i = 0; i < 10; i++) {
    average += analogRead(PC_ALIVE_PIN);  
  }
  average = average / 10;
  Serial.print("Alive: ");
  Serial.println(average);
  return (average < 800);
}

float readPCStillAliveValue() {
  float average = 0.0;
  for (int i = 0; i < 10; i++) {
    average += analogRead(PC_ALIVE_PIN);  
  }
  average = average / 10;
  Serial.print("Alive: ");
  Serial.println(average);
  return average;
}

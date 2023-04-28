
// ===================================
// Arduino Door & Lock State Detector
// ===================================

const int DOOR_SENSOR = 2;
const int LOCK_SENSOR = 3;

// Sensor states
bool doorClosed;
bool lockEngaged;

bool previousDoorClosed;
bool previousLockEngaged;

void setup() {
  Serial.begin(9600);

  pinMode(DOOR_SENSOR, INPUT_PULLUP);
  pinMode(LOCK_SENSOR, INPUT_PULLUP);

  // Initial readings
  delay(50);

  doorClosed = (digitalRead(DOOR_SENSOR) == LOW);
  lockEngaged = (digitalRead(LOCK_SENSOR) == LOW);

  previousDoorClosed = doorClosed;
  previousLockEngaged = lockEngaged;

  printStatus();
}

void loop() {

  // Read both sensors
  bool newDoorState = (digitalRead(DOOR_SENSOR) == LOW);
  bool newLockState = (digitalRead(LOCK_SENSOR) == LOW);

  // Basic debounce
  delay(30);

  if (newDoorState != (digitalRead(DOOR_SENSOR) == LOW)) {
    return;
  }

  if (newLockState != (digitalRead(LOCK_SENSOR) == LOW)) {
    return;
  }

  doorClosed = newDoorState;
  lockEngaged = newLockState;

  // Detect state changes
  if (doorClosed != previousDoorClosed ||
      lockEngaged != previousLockEngaged) {

    printStatus();

    previousDoorClosed = doorClosed;
    previousLockEngaged = lockEngaged;
  }
}

void printStatus() {

  Serial.println("------------------------");

  Serial.print("Door: ");
  Serial.println(doorClosed ? "CLOSED" : "OPEN");

  Serial.print("Lock: ");
  Serial.println(lockEngaged ? "LOCKED" : "UNLOCKED");

  if (doorClosed && lockEngaged) {
    Serial.println("STATUS: SECURE");
  }
  else if (doorClosed && !lockEngaged) {
    Serial.println("STATUS: CLOSED - UNLOCKED");
  }
  else if (!doorClosed && lockEngaged) {
    Serial.println("STATUS: OPEN - BOLT EXTENDED");
  }
  else {
    Serial.println("STATUS: OPEN - UNLOCKED");
  }

  Serial.println("------------------------");
}

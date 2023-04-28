# Arduino Uno Door Sensor & Deadbolt Monitor

## Overview

This document describes a basic Arduino Uno input circuit using:

- An **NC (normally closed) magnetic door contact** on digital pin **D2**
- A **deadbolt microswitch** using its **COM** and **NO** terminals on digital pin **D3**
- Arduino internal pull-up resistors (`INPUT_PULLUP`), so no external pull-up resistors are required for these simple switch inputs

The circuit reports the electrical state of each input over the Serial Monitor. It is a wiring and input-test starting point; it does not implement an alarm, lock actuator, network connection, or other project-specific behavior.

## Files

- `circuit_diagram.svg` — scalable wiring diagram for the connections below.

## Parts

- Arduino Uno
- NC magnetic door contact (two-wire contact)
- Deadbolt-position microswitch with COM and NO terminals
- Jumper wires
- USB cable for programming and Serial Monitor

## Wiring

Disconnect USB power while wiring.

| Arduino Uno | Connect to | Notes |
|---|---|---|
| D2 | One wire of the NC magnetic contact | Door sensor input |
| GND | Other wire of the NC magnetic contact | Contact closes the input to ground in its normal/closed state |
| D3 | Microswitch NO terminal | Deadbolt microswitch input |
| GND | Microswitch COM terminal | When the switch is actuated, COM connects to NO |

Do not connect either switch input to 5V. The sketch enables the Uno's internal pull-ups.

### Input logic

With `INPUT_PULLUP`, an open contact reads `HIGH` and a contact closed to GND reads `LOW`.

- **Magnetic contact on D2:** `LOW` means the NC contact is electrically closed; `HIGH` means it is open. On many NC magnetic contacts, the contact opens when the magnet moves away, but confirm the behavior of your specific sensor with a continuity meter.
- **Microswitch on D3:** because D3 is wired to NO and COM is grounded, `LOW` means COM and NO are connected (switch actuated); `HIGH` means they are not connected (switch released).

The words “door open” and “deadbolt extended/retracted” depend on the physical mounting and switch adjustment. Verify those mechanical states before assigning application meanings.

## Arduino sketch

Upload this test sketch to the Uno:

```cpp
const byte DOOR_PIN = 2;       // NC magnetic contact: D2 to contact, other side to GND
const byte DEADBOLT_PIN = 3;   // Microswitch: NO to D3, COM to GND

void setup() {
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(DEADBOLT_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println(F("Arduino Uno door / deadbolt input test"));
}

void loop() {
  const bool doorContactClosed = (digitalRead(DOOR_PIN) == LOW);
  const bool deadboltSwitchActuated = (digitalRead(DEADBOLT_PIN) == LOW);

  Serial.print(F("Door NC contact: "));
  Serial.println(doorContactClosed ? F("CLOSED (LOW)") : F("OPEN (HIGH)"));

  Serial.print(F("Deadbolt microswitch COM-NO: "));
  Serial.println(deadboltSwitchActuated ? F("CONNECTED / ACTUATED (LOW)")
                                        : F("DISCONNECTED / RELEASED (HIGH)"));

  Serial.println();
  delay(250);
}
```

## Upload and test

1. Wire the circuit with the Uno disconnected from USB.
2. Connect the Uno to your computer with a USB cable.
3. In the Arduino IDE, select **Tools → Board → Arduino Uno**.
4. Select the correct serial port.
5. Upload the sketch.
6. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
7. Operate the magnetic contact and microswitch separately. Confirm the corresponding input changes between `LOW` and `HIGH`.
8. Use a continuity meter to confirm which physical door and deadbolt positions correspond to each electrical state.

## Troubleshooting

- **Input always HIGH:** check that the switch actually closes to GND, and verify the terminal labels (COM/NO/NC).
- **Input always LOW:** check for a short to GND, incorrect terminal selection, or a switch that is permanently closed.
- **States appear reversed:** this can be normal depending on sensor contact type and mechanical mounting. Confirm with a continuity meter and adjust the interpretation in the sketch.
- **Unstable readings:** keep switch wires reasonably short, secure all connections, and consider software debounce if you later use the inputs to trigger actions.

## Safety and limitations

- This is a low-voltage signal circuit only. Do not connect mains voltage to the Arduino or these switches.
- Do not power a lock actuator, solenoid, or motor directly from an Arduino I/O pin. Such loads require an appropriately rated driver, protection components, and a suitable external power supply.
- Test the sensor mechanics before relying on the readings for security or access control.
- This example does not provide tamper detection, fail-safe behavior, alarm handling, or certified security functionality.

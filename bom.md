# Bill of Materials (BOM)
## Arduino Uno Door & Deadbolt Monitor

This bill of materials matches the current `README.md` and `circuit_diagram.svg`.

| Item | Component | Quantity | Specification / notes |
|---|---|---:|---|
| 1 | Arduino Uno | 1 | Uno-compatible board; used as the controller |
| 2 | NC magnetic door contact | 1 | Two-wire, normally closed contact; connect between D2 and GND |
| 3 | Deadbolt-position microswitch | 1 | SPDT microswitch with COM, NO and NC terminals; use COM and NO |
| 4 | Jumper wires | As needed | Male-to-male or other ends appropriate for the selected board and switch terminals |
| 5 | USB cable | 1 | Cable compatible with the specific Arduino Uno board, for programming and USB power |
| 6 | Computer with Arduino IDE | 1 | For uploading the sketch and viewing Serial Monitor output |

## Wiring summary

| Connection | Destination |
|---|---|
| Arduino D2 | One lead of the NC magnetic door contact |
| Arduino GND | Other lead of the NC magnetic door contact |
| Arduino D3 | NO terminal of the deadbolt microswitch |
| Arduino GND | COM terminal of the deadbolt microswitch |
| Microswitch NC | Not connected |

## Notes

- The sketch uses `INPUT_PULLUP` for D2 and D3. External pull-up resistors are not required for the simple switch wiring shown.
- The NC magnetic contact should be verified with a continuity meter. Its actual open/closed behavior depends on the sensor and magnet arrangement.
- The microswitch must be mounted and adjusted so its COM-to-NO transition corresponds to the intended deadbolt position. Verify this mechanically before relying on the reading.
- Quantities for jumper wires depend on the enclosure, mounting locations and wire routing.
- No lock actuator, solenoid, relay, motor driver, external actuator power supply, enclosure, fasteners or alarm device is included. Those parts are not specified by the current circuit.
- Do not drive a lock actuator or other high-current load directly from an Arduino I/O pin.

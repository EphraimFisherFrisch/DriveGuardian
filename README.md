# DriveGuardian
Insert blurb here
## Components
* 3x [Pressure Sensors](https://www.amazon.com/SENSING-RESISTOR-SQUARE-1oz-22LBS-SPACING/dp/B00B887DBC/) ($15.53 each; $46.59 total)
* 1x [Piezo Sensor](https://www.amazon.com/MakerHawk-Analog-Ceramic-Vibration-Arduino/dp/B07KS5NV4V) ($1.50)
* 1x [Servo](https://www.amazon.com/Micro-Helicopter-Airplane-Remote-Control/dp/B072V529YD) ($1.88)
* 1x Arduino Nano (Any ATMega328-based Arduino should work) ($5.75)
* 1x NodeMCU ($7.99)
* 3x 10k Ohm Resistors ($0.03)
* 6x AA Battery Holder ($2.99)
* 6x AA Batteries 

**Total Price: $66.73**

## Circuit Setup
![DriveGuardian](https://user-images.githubusercontent.com/104529664/235731490-873c727c-a60f-4a93-a61c-69f150ae1ba0.png)

The components should be wired as follows:
| Component | Arduino Nano |
| --------- | ---- |
| Pressure Sensor | A0 |
| Pressure Sensor | A1 |
| Pressure Sensor | A2 |
| Piezo Sensor | A3 |
| Servo | D5 |

The Arduino Nano should be wired to the NodeMCU as follows:
| Arduino Nano | NodeMCU | Description |
| ---- | ------- | ----------- |
| D2 | D6 | Data line for servo status |
| D8 | D1 | Data line for first pressure sensor |
| D9 | D2 | Data line for second pressure sensor |
| D10 | D3 | Data line for third pressure sensor |
| D11 | D5 | Data line for piezo sensor |

## Code

### Arduino Nano
The following libraries must be installed for the Arduino Nano:
* `Servo.h`

The following is a programming flowchart for the Arduino Nano code:

![DriveGuardian Nano Flowchart](https://user-images.githubusercontent.com/104529664/236548992-43ea7e50-f01b-461d-93e6-13767b1665e2.png)

### NodeMCU
The following libraries must be installed for the NodeMCU:
* `ESP8266WiFi.h`
* `BlynkSimpleEsp8266.h`
* `ezTime.h`

The following is a programming flowchart for the NodeMCU code:

![DriveGuardian NodeMCU Flowchart](https://github.com/EphraimFisherFrisch/DriveGuardian/assets/104529664/4c36c211-d6ec-4db9-901e-8222d9908b89)

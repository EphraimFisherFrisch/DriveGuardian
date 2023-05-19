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

**Total Cost: $66.73**

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

The following is a pseudocode demonstration of the Arduino Nano code:

```
Pressure Sensor One Input is A0
Pressure Sensor Two Input is A1
Pressure Sensor Three Input is A2
Piezo Sensor Input is A3
Configure servo on D5

Servo Data Line is D2
Pressure Sensor One Data Line is D8
Pressure Sensor Two Data Line is D9
Pressure Sensor Three Data Line is D10
Piezo Sensor Data Line is D11

Do once for setup:
  Configure all data lines except for the servo data line as output pins
  Configure the servo data line as an input pin
  Write initial LOW values to all data lines
  Set up the servo data line as an interrupt to trigger the following whenever it changes status:
    If the data line is high:
      Close the servo
    Else:
      Open the servo

Constantly loop through the following:
  Read pressure sensors and piezo sensor and update data lines accordingly
  Wait 20 ms
```

### NodeMCU
The following libraries must be installed for the NodeMCU:
* `ESP8266WiFi.h`
* `BlynkSimpleEsp8266.h`
* `ezTime.h`

The following is a programming flowchart for the NodeMCU code:

![DriveGuardian NodeMCU Flowchart](https://github.com/EphraimFisherFrisch/DriveGuardian/assets/104529664/4c36c211-d6ec-4db9-901e-8222d9908b89)

The following is a pseudocode demonstration of the NodeMCU code:
```
Pressure Sensor One Data Line is D1
Pressure Sensor Two Data Line is D2
Pressure Sensor Three Data Line is D3
Piezo Sensor Data Line is D5
Servo Data Line is D6

Do once for setup:
  Configure all data lines except for the servo data line as input pins
  Configure servo data line as an output pin
  Connect to the Blynk servers
  
Do every second:
  Read data lines and update status of pressure sensors and piezo sensors on Blynk
  If DriveGuardian is in override mode:
    Set the servo data line to low
  Otherwise, if DriveGuardian is in lock mode:
    Set the servo data line to high if the piezo sensor is low, otherwise set it to low
  Otherwise, if it is past curfews imposed by law (11PM-5AM):
    Set the servo data line to high if the piezo sensor is low, otherwise set it to low
  Otherwise, if two or more pressure sensors are high:
    Set the servo data line to high if the piezo sensor is low, otherwise set it to low
  Otherwise, if a custom curfew is enabled:
    If it is during a time when the custom curfew would bar driving:
      Set the servo data line to high if the piezo sensor is low, otherwise set it to low
  If none of the above conditions are met:
    Set the servo data line to low
```

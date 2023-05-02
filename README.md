# DriveGuardian
Insert blurb here
# Components
Insert components here
# Circuit Setup
![DriveGuardian](https://user-images.githubusercontent.com/104529664/235731490-873c727c-a60f-4a93-a61c-69f150ae1ba0.png)

The components should be wired as follows:
| Component | Nano |
| --------------- | ----------------- |
| Pressure Sensor | A0 |
| Pressure Sensor | A1 |
| Pressure Sensor | A2 |
| Piezo Sensor | A3 |
| Servo | D5 |

The Nano should be wired to the NodeMCU as follows:
| Nano | NodeMCU | Description |
| ---- | ------- | ----------- |
| D2 | D6 | Signals an interrupt to open or close the servo |
| D8 | D1 | Transfers data from first pressure sensor to NodeMCU |
| D9 | D2 | Transfers data from second pressure sensor to NodeMCU |
| D10 | D3 | Transfers data from third pressure sensor to NodeMCU |
| D11 | D5 | Transfers data from piezo sensor to NodeMCU |

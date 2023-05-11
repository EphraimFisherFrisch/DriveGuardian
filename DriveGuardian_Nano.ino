#include <Servo.h>

#define SEAT_ONE_PIN A0
#define SEAT_TWO_PIN  A1
#define SEAT_THREE_PIN A2
#define PIEZO_PIN A3
#define SEAT_ONE_OUT 8
#define SEAT_TWO_OUT 9
#define SEAT_THREE_OUT 10
#define PIEZO_OUT 11

#define SERVO_INTERRUPT_PIN 2
#define SERVO_PIN 5
#define SERVO_CLOSE_VALUE 0
#define SERVO_OPEN_VALUE 115

//#define DG_DB // Uncomment this line to enable Serial prints for debugging

Servo servo;
volatile bool servoStatus;

// Converts analogRead of pressure sensor to a boolean True if above a certain threshold
bool seatStatus(char pin) {
  if (analogRead(pin) < 15) {
    return false;
  }
  // Get a second reading after a 1ms delay to eliminate incorrect noise readings
  delay(1);
  if (analogRead(pin) < 15) {
    return false;
  }
  return true;
}

// Converts analogRead of piezo sensor to a boolean True if above a certain threshold
bool piezoStatus(char pin) {
  if (analogRead(pin) < 15) {
    return false;
  }
  // Get a second reading after a 1ms delay to eliminate incorrect noise readings
  delay(1);
  if (analogRead(pin) < 15) {
    return false;
  }
  return true;
}

// Handles receiving signals from NodeMCU regarding the servo
void updateServo() {
  #ifdef DG_DB
  Serial.print("INT ");
  Serial.println(digitalRead(2));
  #endif

  // If the Nano is receiving a HIGH signal from the NodeMCU, set the servoStatus to close
  if (digitalRead(2) == HIGH) {
    servoStatus = true;
  } else { // If it is receiving a LOW signal, set servoStatus to stay open
    servoStatus = false;
  }
}

void setup() {
  #ifdef DG_DB
  Serial.begin(9600);
  #endif

  pinMode(SEAT_ONE_OUT, OUTPUT);
  pinMode(SEAT_TWO_OUT, OUTPUT);
  pinMode(SEAT_THREE_OUT, OUTPUT);
  pinMode(PIEZO_OUT, OUTPUT);
  pinMode(SERVO_INTERRUPT_PIN, INPUT);
  servo.attach(SERVO_PIN);

  digitalWrite(SEAT_ONE_OUT, LOW);
  digitalWrite(SEAT_TWO_OUT, LOW);
  digitalWrite(SEAT_THREE_OUT, LOW);
  digitalWrite(PIEZO_OUT, LOW);
  servo.write(SERVO_OPEN_VALUE);

  // Call updateServo() whenever the pin receiving the instructions for the servo from NodeMCU changes
  attachInterrupt(digitalPinToInterrupt(SERVO_INTERRUPT_PIN), updateServo, CHANGE);
}

void loop() {
  #ifdef DG_DB
  Serial.print("Seat One: ");
  Serial.print(seatStatus(SEAT_ONE_PIN));
  Serial.print(" ");
  Serial.println(analogRead(SEAT_ONE_PIN));
  Serial.print("Seat Two: ");
  Serial.print(seatStatus(SEAT_TWO_PIN));
  Serial.print(" ");
  Serial.println(analogRead(SEAT_TWO_PIN));
  Serial.print("Seat Three: ");
  Serial.print(seatStatus(SEAT_THREE_PIN));
  Serial.print(" ");
  Serial.println(analogRead(SEAT_THREE_PIN));
  Serial.print("Piezo: ");
  Serial.print(piezoStatus(PIEZO_PIN));
  Serial.print(" ");
  Serial.println(analogRead(PIEZO_PIN));
  #endif

  // Actualize the changes made in updateServo()
  if (servoStatus) {
    servo.write(SERVO_CLOSE_VALUE);
  } else {
    servo.write(SERVO_OPEN_VALUE);
  }

  // Send data to NodeMCU for handling
  digitalWrite(SEAT_ONE_OUT, seatStatus(SEAT_ONE_PIN));
  digitalWrite(SEAT_TWO_OUT, seatStatus(SEAT_TWO_PIN));
  digitalWrite(SEAT_THREE_OUT, seatStatus(SEAT_THREE_PIN));
  digitalWrite(PIEZO_OUT, piezoStatus(PIEZO_PIN));
  #ifdef DG_DB
  delay(1000);
  #else
  delay(20);
  #endif
}
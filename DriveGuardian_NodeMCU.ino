#define BLYNK_TEMPLATE_ID           "TMPLcFCd6rvo"
#define BLYNK_TEMPLATE_NAME         "DriveGuardian"
#define BLYNK_AUTH_TOKEN            "pfhjRGldoeS36w5NO_e4kSj5G5e_HG4p"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ezTime.h>

#define SEAT_ONE_IN 5
#define SEAT_TWO_IN 4
#define SEAT_THREE_IN 0
#define PIEZO_IN 14
#define SERVO_STATUS_OUT 12

//#define DG_DB // Uncomment this line to enable Serial prints for debugging

char ssid[] = "iPhoneEphraim";
char pass[] = "ephraimhotspot";

BlynkTimer timer;
Timezone timeObject;
int settingStatus;

// Called when connected to the Blynk server
BLYNK_CONNECTED() {
  // Get the current UTC time
  Blynk.sendInternal("utc", "time");
}

BLYNK_WRITE(InternalPinUTC) {
  // Pass the current UTC time into the ezTime library
  const uint64_t utc_time = param[1].asLongLong();
  UTC.setTime(utc_time / 1000, utc_time % 1000);
}

// Called whenever the settings are changed from Blynk
BLYNK_WRITE(V0) {
  #ifdef DG_DB
  Serial.print("settingStatus changed to: ");
  Serial.println(param.asInt());
  #endif

  settingStatus = param.asInt();
}

bool servoStatus() {
  // If in override mode, keep the servo open
  if (settingStatus == 2) {
    return false;
  } else if (settingStatus == 0) { // If in lock mode, turn off if the car is off
    return !digitalRead(PIEZO_IN);
  } else { // When in normal functionality check for time and pressure sensor restrictions
    if (timeObject.hour() >= 23 || timeObject.hour() <= 4) {
      return !digitalRead(PIEZO_IN);
    } else if (digitalRead(SEAT_ONE_IN) + digitalRead(SEAT_TWO_IN) + digitalRead(SEAT_THREE_IN) > 1) {
      return !digitalRead(PIEZO_IN);
    }
    return false;
  }
}

void everySecond() {
  #ifdef DG_DB
  Serial.print("Seat One: ");
  Serial.println(digitalRead(SEAT_ONE_IN));
  Serial.print("Seat Two: ");
  Serial.println(digitalRead(SEAT_TWO_IN));
  Serial.print("Seat Three: ");
  Serial.println(digitalRead(SEAT_THREE_IN));
  Serial.print("Piezo: ");
  Serial.println(digitalRead(PIEZO_IN));
  #endif

  // Send data received from Nano to Blynk
  Blynk.virtualWrite(V4, digitalRead(SEAT_ONE_IN));
  Blynk.virtualWrite(V5, digitalRead(SEAT_TWO_IN));
  Blynk.virtualWrite(V6, digitalRead(SEAT_THREE_IN));
  Blynk.virtualWrite(V1, digitalRead(PIEZO_IN));

  // Send instruction to Nano to open or close servo
  digitalWrite(SERVO_STATUS_OUT, servoStatus());
}

void setup() {
  #ifdef DG_DB
  Serial.begin(9600);
  #endif

  pinMode(SEAT_ONE_IN, INPUT);
  pinMode(SEAT_TWO_IN, INPUT);
  pinMode(SEAT_THREE_IN, INPUT);
  pinMode(PIEZO_IN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SERVO_STATUS_OUT, OUTPUT);
  
  digitalWrite(SERVO_STATUS_OUT, LOW); // Send initial instruction to Nano to keep the servo open
  digitalWrite(LED_BUILTIN, HIGH); // Turn built-in LED off

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to Blynk
  digitalWrite(LED_BUILTIN, LOW); // Turn built-in LED on once connected to Blynk

  // Set up a timer to call everySecond() every second
  timer.setInterval(1000L, everySecond);

  // Set up time zone
  timeObject.setLocation("America/New_York");

  // Reset settings to normal mode instead of override or lock
  Blynk.virtualWrite(V0, 1);
  settingStatus = 1;
}

void loop() {
  Blynk.run();
  timer.run();
}
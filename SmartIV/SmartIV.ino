// /*
//   Main control loop for IV Monitoring System with Smart Sampling Rate
// */

#include "Sensors.h"
#include "Alarm.h"
#include "DataLog.h"
#include "Compute.h"
#include "Display.h"

#define BAUD_RATE 9600
// Variables to control for flow rate monitoring
int calibrateDropCount;
int dropCount;
int dropSensed;
int missedDropCount;
int consecutiveMissedDropCount;
unsigned long oldDropTime;
unsigned long newDropTime;
unsigned long oldDeltaT;
unsigned long newDeltaT;
unsigned long turnOnTime;
int deltaTBound;
unsigned long totalVolume;
unsigned long missedVolume;
int dangerAlarm;
int warningAlarm;

// Flags for each task
int SensorsActive;
int ComputeActive;
int DataLogActive;
int DisplayActive;
int AlarmActive;

// Variable to keep track of sensor configuration
int SensorsState;
unsigned long prevTime;

const int DIN_PIN = 8;   // Pin connected to MAX7219 DIN
const int CS_PIN = 9;    // Pin connected to MAX7219 CS
const int CLK_PIN = 10;  // Pin connected to MAX7219 CLK

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);  // Create a LedControl object
void setup() {

  // default values for global variables
  SensorsActive = 1;
  ComputeActive = 0;
  DataLogActive = 0;
  DisplayActive = 1;
  AlarmActive = 0;

  dropSensed = FALSE;
  SensorsState = TRUE;
  calibrateDropCount = 0;
  dropCount = 0;
  missedDropCount = 0;
  consecutiveMissedDropCount = 0;
  oldDropTime = 0;
  newDropTime = 0;
  oldDeltaT = 180000;
  newDeltaT = 0;
  deltaTBound = 2000;

  totalVolume = 0;
  missedVolume = 0;
  SensorsState = 1;

  dangerAlarm = FALSE;
  warningAlarm = FALSE;

  prevTime = 0;

  // set appropriate input/output config for sensor pins
  pinMode(TOP_SENSOR_POWER_PIN, OUTPUT);
  pinMode(TOP_SENSOR_OUTPUT_PIN, INPUT_PULLUP);
  pinMode(BOT_SENSOR_POWER_PIN, OUTPUT);
  pinMode(BOT_SENSOR_OUTPUT_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(TOP_SENSOR_OUTPUT_PIN), record, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOT_SENSOR_OUTPUT_PIN), record, FALLING);

  digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
  digitalWrite(BOT_SENSOR_POWER_PIN, HIGH);

  // Initialize serial port with desired baud rate
  Serial.begin(BAUD_RATE);
}

void loop() {
  if (SensorsActive) {
    SensorsTask();
  }

  if (ComputeActive) {
    ComputeTask();
  }

  // if (DataLogActive) {
  //   DataLogTask();
  // }

  // if (DisplayActive) {
  //   DisplayTask();
  // }

  // if (AlarmActive) {
  //   AlarmTask();
  // }

  if (SensorsState == FALSE) {
    unsigned long currTime = millis();
    // timer behavior that controls the turning on of sensor pairs
    // noInterrupts();
    // delay(oldDeltaT - deltaTBound*1000);
    // if time elapsed is greater than the old delta t - 2 seconds, then turn back on
    if (currTime - oldDropTime >= (oldDeltaT - deltaTBound - DEBOUNCE_DELAY)) {
      // Serial.print("Current Delta vs. comparator is: "); Serial.print(currTime - oldDropTime);
      // Serial.print(","); Serial.println(oldDeltaT - deltaTBound);
      noInterrupts();
      digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
      digitalWrite(BOT_SENSOR_POWER_PIN, HIGH);
      // dropSensed = FALSE;
      // SensorsState = TRUE;
      interrupts();
      delay(DEBOUNCE_DELAY);
      dropSensed = FALSE;
      SensorsState = TRUE;
      turnOnTime = millis();
    }
    // interrupts();
  }
  // delay(50);
  // Serial.println(digitalRead(2));
}

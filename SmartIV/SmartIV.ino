// /*
//   Main control loop for IV Monitoring System with Smart Sampling Rate
// */

#include "Sensors.h"
#include "Alarm.h"
#include "DataLog.h"
#include "Compute.h"
#include "Display.h"

#define BAUD_RATE 9600
#define MAX_BUFFER_LENGTH 10

// Variables to control for flow rate monitoring buffer
int maxDropBufferLength = MAX_BUFFER_LENGTH;
int dropTimeBuffer[MAX_BUFFER_LENGTH];
int currDropBufferLength;
int writePtr;
int dropCount;
unsigned long oldDropTime;
unsigned long newDropTime;

// Flags for each task
int SensorsActive;
int ComputeActive;
int DataLogActive;
int DisplayActive;
int AlarmActive;

// Variable to keep track of sensor configuration
int SensorState;
void setup() {

  // default values for global variables
  SensorsActive = 1;
  ComputeActive = 0;
  DataLogActive = 0;
  DisplayActive = 1;
  AlarmActive = 0;

  currDropBufferLength = 0;
  writePtr = 0;
  dropCount = 0;

  SensorState = 1;

  // set appropriate input/output config for sensor pins
  pinMode(TOP_SENSOR_POWER_PIN, OUTPUT);
  pinMode(TOP_SENSOR_OUTPUT_PIN, INPUT);
  pinMode(BOT_SENSOR_POWER_PIN, OUTPUT);
  pinMode(BOT_SENSOR_OUTPUT_PIN, INPUT);

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

  if (DataLogActive) {
    DataLogTask();
  }

  if (DisplayActive) {
    DisplayTask();
  }

  if (AlarmActive) {
    AlarmTask();
  }
}

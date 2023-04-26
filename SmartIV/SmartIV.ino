/*
  Main control loop for IV Monitoring System with Smart Sampling Rate

*/

#include <Sensors.h>
#include <Alarm.h>
#include <DataLog.h>
#include <Compute.h>
#include <Display.h>

constexpr BAUD_RATE = 9600;
int SlowSensorActive;
int FastSensorActive;
int DataLogActive;
int DisplayActive;
int AlarmActive;

void setup() {

  SensorsActive = 1;
  ComputeAlive = 0;
  DataLogActive = 0;
  DisplayActive = 1;
  AlarmActive = 0;

  Serial.begin(BAUD_RATE);
}

void loop(){

  SensorsTask();
  ComputeTask();
  DataLogActive();
  DisplayActive();
  AlarmActive();
  
}

void ComputeTask() {
  
}

void DataLogTask() {
  
}

void DisplayTask() {
  
}

void AlarmTask() {
  
}

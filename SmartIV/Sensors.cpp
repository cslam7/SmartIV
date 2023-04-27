/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/
#include <Arduino.h>
#include "Sensors.h"

void SensorsTask() {

  // When sampling needs to be fast
  if (SensorState == BOTH_ON) {
    digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
    // digitalWrite(BOT_SENSOR_POWER, HIGH);
    attachInterrupt(digitalPinToInterrupt(TOP_SENSOR_OUTPUT_PIN), record, FALLING);
    // attachInterrupt(digitalPinToInterrupt(BOT_SENSOR_OUTPUT), record, RISING);
  }
}

void record() {
  dropCount++;
  // if initial drop, then start timer
  // otherwise, compute time difference and store in buffer
  if (dropCount == 1) {
    oldDropTime = millis();
  } else {
    newDropTime = millis();
    dropTimeBuffer[writePtr++] = newDropTime - oldDropTime;
    writePtr %= maxDropBufferLength;
    oldDropTime = newDropTime;
    ComputeActive = 1;
  }
}
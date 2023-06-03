/*
  All code related to computing flow rates from sensor outputs
*/
#include <Arduino.h>
#include "Compute.h"

void ComputeTask() {

  missedVolume = missedDropCount / GTT;
  float missedVolumeThreshold = (millis() * ML_DANGER) / (3600.0 * 1000);
  if (missedVolume > missedVolumeThreshold) {
    dangerAlarm = TRUE;
  }
  if (consecutiveMissedDropCount == 1) {
    warningAlarm = 1;
  } else if (consecutiveMissedDropCount >= 2) {
    consecutiveMissedDropCount = 0;
    calibrateDropCount = 0;
    warningAlarm = 2;
  } else {
    warningAlarm = 0;
  }
  ComputeActive = FALSE;
  AlarmActive = TRUE;
}

// when computd flow rate exceed threshold, set alarm
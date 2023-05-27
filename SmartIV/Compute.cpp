/*
  All code related to computing flow rates from sensor outputs
*/
#include <Arduino.h>
#include "Compute.h"

// extern int ComputeAlive;
void ComputeTask() {

  //totalVolume = dropCount / GTT;
  missedVolume = missedDropCount / GTT;
  if (missedVolume > ML_DANGER) {
    dangerAlarm = TRUE;
  }
  if (consecutiveMissedDropCount == 1) {
    warningAlarm = TRUE;
  } else if (consecutiveMissedDropCount >= 2) {
    consecutiveMissedDropCount = 0;
    calibrateDropCount = 0;
  }
  // compute the flow rate here
  ComputeActive = FALSE;
  AlarmActive = TRUE;
}

// when computd flow rate exceed threshold, set alarm
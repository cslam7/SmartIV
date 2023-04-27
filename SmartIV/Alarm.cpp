/*
  All code related to changing LEDS to display system state
*/
#include <Arduino.h>
#include "Alarm.h"

extern int AlarmActive;

void AlarmTask() {
  if (AlarmActive) {
    Serial.println("blah");
  }
}
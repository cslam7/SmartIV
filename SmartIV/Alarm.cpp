/*
  All code related to changing LEDS to display system state
*/
#include <Arduino.h>
#include "Alarm.h"

unsigned long lastLEDBlink = 0;

void AlarmTask() {
  if (dangerAlarm == TRUE) {
    // set RED danger LED
  } else {
    // turn off RED danger LED
  }

  if (warningAlarm == TRUE) {
    // blink yellow warningLED
    // enable timer to blink yellow LED at 5 Hz
  } else {
    //disables timer
  }
  // if calibrate
  if (calibrate < 2) {
    // set YELLOW warning LED
  } else {
    // turn off YELLOW warning LED
  }
}

// Put this function a loop to blink the onboard LED every period_ms
void blink(unsigned long period_ms) 
{
  // change to desired LEDS
  if (millis() - lastLEDBlink > period_ms)
  {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // toggle led state
      lastLEDBlink = millis();
  }
}
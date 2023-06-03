/*
  All code related to changing LEDS to display system state
*/
#include <Arduino.h>
#include "Alarm.h"

unsigned long lastLEDBlink = 0;
int warningState = 0;
void AlarmTask() {
  if (dangerAlarm == TRUE) {
    digitalWrite(DANGER_LED_PIN, 1);
  } else {
    // turn off RED danger LED
    digitalWrite(DANGER_LED_PIN, 0);
  }

  if (warningAlarm == 1) {
    // blink yellow warning LED
    blink(WARN_AND_CALIBRATE_LED_PIN, 500);
  } else if (warningAlarm == 2) {
    // turn on yellow warning LED
    digitalWrite(WARN_AND_CALIBRATE_LED_PIN, 1);
  } else {
    digitalWrite(WARN_AND_CALIBRATE_LED_PIN, 0);
  }
}

// Put this function a loop to blink the onboard LED every period_ms
void blink(int pin, unsigned long period_ms) 
{
  // change to desired LEDS
  if (millis() - lastLEDBlink > period_ms)
  {
    warningState ^= warningState;
    digitalWrite(pin, warningState);  // toggle led state
    lastLEDBlink = millis();
  }
}
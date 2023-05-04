/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/
#include <Arduino.h>
#include "Sensors.h"

unsigned long int lastISRFired = 100;
bool dropSensed = FALSE;
void SensorsTask() {
  // When sampling needs to be fast
  //if (SensorStates == BOTH_ON) {
  digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
    // digitalWrite(BOT_SENSOR_POWER, HIGH);
  attachInterrupt(digitalPinToInterrupt(TOP_SENSOR_OUTPUT_PIN), record, FALLING);
  if (dropSensed == TRUE) {
      noInterrupts();
      if((millis() - lastISRFired) > 500){
        dropCount++;
        //Serial.println(dropCount);
        // if initial drop, then start timer
        // otherwise, compute time difference and store in buffer
        if (dropCount == 1) {
          oldDropTime = millis();
          Serial.println("///ignore");
        } else {
          newDropTime = millis();
          Serial.println(newDropTime-oldDropTime);
          dropTimeBuffer[writePtr++] = newDropTime - oldDropTime;
          writePtr %= maxDropBufferLength;
          oldDropTime = newDropTime;
          ComputeActive = 1;
        }
        lastISRFired = millis();
      }
      interrupts();
      dropSensed = FALSE;
  }

}

void record() {
  dropSensed = TRUE;
}
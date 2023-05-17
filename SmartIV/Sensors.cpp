/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/
#include <Arduino.h>
#include "Sensors.h"

// unsigned long int lastISRFired = 100;

bool dropSensed = FALSE;
int oldtime = 0;
int ledState = 0;

void SensorsTask() {

  if (dropSensed == TRUE) {
    noInterrupts();
    if((millis() - oldDropTime) > 500){
      dropCount++;
      //Serial.println(dropCount);
      // if initial drop, then start timer
      // otherwise, compute time difference and store in buffer
      if (dropCount == 1) {
        oldDropTime = millis();
        Serial.println("///ignore");
      } else {
        newDropTime = millis();
      // Output is timestamp,sensor,dropCount,deltaDropTime,flowrate
        
        Serial.print(",");
        Serial.print(dropCount);
        Serial.print(",");
        Serial.print(newDropTime-oldDropTime);
        Serial.print(",");
        Serial.println((3600) / (20 * (newDropTime-oldDropTime)/1000));
        dropTimeBuffer[writePtr++] = newDropTime - oldDropTime;
        writePtr %= maxDropBufferLength;
        oldDropTime = newDropTime;
        ComputeActive = 1;
      }
    }
    interrupts();
    dropSensed = FALSE;
  }
}

void record() {
  dropSensed = TRUE;
}
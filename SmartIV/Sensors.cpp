/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/
#include <Arduino.h>
#include "Sensors.h"

int oldtime = 0;
int ledState = 0;

void SensorsTask() {

  // Serial.println("At least entering task");
  if (dropSensed == TRUE && SensorsState == TRUE) {
    // Serial.println("Am I sensing anything?");
    dropSensed = FALSE;
    // if a drop is sensed, check if enough time has passed (1s)
    // if so, if not calibrated, then calibrate
    // keep power on, turn on interrupts
    // if not, then use the drop time as new reference
    // dturn off power, turn off interrupts
    if ((millis() - oldDropTime) > 500) {
      // dropSensed = FALSE;
      Serial.print("Calibration count is: ");
      Serial.print(calibrateDropCount);
      Serial.print("Curr and old drop time is: ");
      Serial.print(millis()/1000.0);
      Serial.print(", ");
      Serial.println(oldDropTime/1000.0);
      // SensorsActive = FALSE;
      ComputeActive = TRUE;
      newDropTime = millis();
      if (calibrateDropCount < 2) {
        dropCount++;
        calibrateDropCount++;
        consecutiveMissedDropCount = 0;
        if (calibrateDropCount == 2) {
          oldDeltaT = newDropTime - oldDropTime;
          SensorsState = FALSE;
          Serial.println("OFF");
          digitalWrite(TOP_SENSOR_POWER_PIN, LOW);
          digitalWrite(BOT_SENSOR_POWER_PIN, LOW);
          dropSensed = FALSE;
          Serial.print("To turn back on, old Delta T is : "); Serial.println(oldDeltaT);
        }
        oldDropTime = newDropTime;
        return;
      } else {      
        // if missed drop, also turn off power
        if (newDropTime - oldDropTime > (oldDeltaT + deltaTBound)) {
          missedDropCount++;
          consecutiveMissedDropCount++;
          Serial.print("Long : "); Serial.print(millis() - oldDropTime);
          Serial.print(" , "); Serial.println(oldDeltaT);
          if (consecutiveMissedDropCount == 2) {
            return;
          }
        } else { // if only miss one consecutive, keep old interval
          // Output is timestamp,sensor,dropCount,deltaDropTime,flowrate
          newDeltaT = newDropTime - oldDropTime;
          Serial.print("Valid: "); Serial.print(millis() - oldDropTime);
          Serial.print(" , "); Serial.println(newDeltaT);
          dropCount++;
          consecutiveMissedDropCount = 0;
          SensorsState = FALSE;
          DisplayActive = TRUE;
          oldDeltaT = newDeltaT;
        }
        digitalWrite(TOP_SENSOR_POWER_PIN, LOW);
        digitalWrite(BOT_SENSOR_POWER_PIN, LOW);
        SensorsState = FALSE;
      }
      oldDropTime = newDropTime;
      return;
    }
    dropSensed = FALSE;
  }

  // keeps light off if not in calibration and the sensors are on, after four seconds turn off the pins
  if (millis() - turnOnTime >= (2*deltaTBound) && calibrateDropCount >= 2 && SensorsState == TRUE) {
    consecutiveMissedDropCount++;
    missedDropCount++;
    if (consecutiveMissedDropCount == 1) {
      Serial.println("Missed drop detected, turning off");
      Serial.println(consecutiveMissedDropCount);
      digitalWrite(TOP_SENSOR_POWER_PIN, LOW);
      digitalWrite(BOT_SENSOR_POWER_PIN, LOW);
      SensorsState = FALSE;
      oldDropTime = millis() - deltaTBound;
    } else {
      Serial.println("Recalibration required");
    }
    ComputeActive = TRUE;
  }
}

void record() {
  if (SensorsState == TRUE) {
    dropSensed = TRUE;
  }
  // Serial.println("Interrupt");
  // Serial.print(digitalRead(2));
  // Serial.print(", ");
  // Serial.println(digitalRead(3));
}
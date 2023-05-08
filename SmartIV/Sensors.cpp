/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/
#include <Arduino.h>
#include "Sensors.h"

// unsigned long int lastISRFired = 100;

bool dropSensed = FALSE;
bool dropSensed2 = FALSE;

int oldtime = 0;
int ledState = 0;
unsigned long previousMillis;
unsigned long interval = 5000;
void SensorsTask() {
  // When sampling needs to be fast
  //if (SensorStates == BOTH_ON) {
  // if (millis() - previousMillis >= interval) {
  //   // save the last time you blinked the LED
  //   previousMillis = millis();

  //   // if the LED is off turn it on and vice-versa:
  //   if (ledState == LOW) {
  //     digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
  //   } else {
  //     digitalWrite(TOP_SENSOR_POWER_PIN, LOW);
  //   }
  //   ledState ^= 1;
  //   // // set the LED with the ledState of the variable:
  //   // digitalWrite(ledPin, ledState);
  // }
  // digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
  // digitalWrite(BOT_SENSOR_POWER, HIGH);
  attachInterrupt(digitalPinToInterrupt(TOP_SENSOR_OUTPUT_PIN), record, FALLING);
  attachInterrupt(digitalPinToInterrupt(BOT_SENSOR_OUTPUT_PIN), record2, FALLING);
  if (dropSensed == TRUE) {
      // noInterrupts();
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
          Serial.print("top,");
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
      // interrupts();
      dropSensed = FALSE;
  }
  if (dropSensed2 == TRUE) {
    // noInterrupts();
    if((millis() - oldDropTime2) > 500){
      dropCount2++;
      //Serial.println(dropCount);
      // if initial drop, then start timer
      // otherwise, compute time difference and store in buffer
      if (dropCount2 == 1) {
        oldDropTime2 = millis();
        Serial.println("///ignore");
      } else {
        newDropTime2 = millis();
        // Output is timestamp,sensor,dropCount,deltaDropTime,flowrate
        
        Serial.print(",");
        Serial.print("bot,");
        Serial.print(dropCount2);
        Serial.print(",");
        Serial.print(newDropTime2-oldDropTime2);
        Serial.print(",");
        Serial.println((3600) / (20 * (newDropTime2-oldDropTime2)/1000));
        dropTimeBuffer[writePtr++] = newDropTime2 - oldDropTime2;
        writePtr2 %= maxDropBufferLength2;
        oldDropTime2 = newDropTime2;
        ComputeActive = 1;
      }
    }
    // interrupts();
    dropSensed2 = FALSE;
  }

}

void record() {
  dropSensed = TRUE;
}

void record2() {
  dropSensed2 = TRUE;
}
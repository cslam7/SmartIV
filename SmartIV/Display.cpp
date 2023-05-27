/*
  All code related to interfacing with the optical sensors
  and corresponding control logic
*/

#include "Display.h"

extern int DisplayActive;
void DisplayTask() {

  Serial.print(",");
  Serial.print(dropCount);
  Serial.print(",");
  Serial.println(oldDeltaT);
  DisplayActive = FALSE;
}
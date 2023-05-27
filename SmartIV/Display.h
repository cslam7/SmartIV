/*
  Function prototypes for Display.c
*/
#include <LedControl.h>
#include <Arduino.h>

#define TRUE 1
#define FALSE 0
extern int DisplayActive;
extern int dropCount;
extern unsigned long oldDropTime;
extern unsigned long newDropTime;
extern unsigned long oldDeltaT;
extern unsigned long newDeltaT;
//  Logic to control LEDS for flow rate display
void DisplayTask();
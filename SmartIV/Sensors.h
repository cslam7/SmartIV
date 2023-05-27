/*
  Function prototypes for Sensors.cpp
*/

#define TOP_SENSOR_POWER_PIN 6
#define TOP_SENSOR_OUTPUT_PIN 3
#define BOT_SENSOR_POWER_PIN 8
#define BOT_SENSOR_OUTPUT_PIN 2

#define TRUE 1
#define FALSE 0
#define DEBOUNCE_DELAY 500
extern int SensorsActive;
extern int ComputeActive;
extern int DisplayActive;
extern int dropSensed;
extern int dropCount;
extern int missedDropCount;
extern int consecutiveMissedDropCount;
extern unsigned long oldDropTime;
extern unsigned long newDropTime;
extern unsigned long oldDeltaT;
extern unsigned long newDeltaT;
extern unsigned long turnOnTime;
extern int deltaTBound;
extern int calibrateDropCount;
extern int SensorsState;

//  Logic to control for smart sampling and sleep states
void SensorsTask();

// ISR Logic to record drop time
void record();
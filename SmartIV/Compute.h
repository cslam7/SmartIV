/*
  Function prototypes for Compute.cpp
*/
#define TRUE 1
#define FALSE 0
#define GTT 20.0
#define NEONATE_DANGER_RATIO 0.012
#define ML_DANGER 0.5
extern int ComputeAlive;
extern int dropCount;
extern unsigned long totalVolume;
extern int missedDropCount;
extern unsigned long missedVolume;
extern int consecutiveMissedDropCount;
// extern unsigned long flowRate;
extern unsigned long oldDeltaT;

extern int dangerAlarm;
extern int warningAlarm;
extern int calibrateDropCount;
extern int ComputeActive;
extern int AlarmActive;
//  Logic to control for smart sampling and sleep states
void ComputeTask();
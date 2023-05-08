/*
  Function prototypes for Sensors.cpp
*/

#define TOP_SENSOR_POWER_PIN 6
#define TOP_SENSOR_OUTPUT_PIN 3
#define BOT_SENSOR_POWER_PIN 8
#define BOT_SENSOR_OUTPUT_PIN 2

#define TRUE 1
#define FALSE 0
extern int SensorsActive;
extern int ComputeActive;
extern int maxDropBufferLength;
extern int dropTimeBuffer[];
extern int writePtr;
extern int dropCount;
extern unsigned long oldDropTime;
extern unsigned long newDropTime;

//copies
extern int maxDropBufferLength2;
extern int dropTimeBuffer2[];
extern int writePtr2;
extern int dropCount2;
extern unsigned long oldDropTime2;
extern unsigned long newDropTime2;

extern int SensorState;

enum SensorStates {
  BOTH_ON = 1,
  BOTH_OFF = 2
};

//  Logic to control for smart sampling and sleep states
void SensorsTask();

// ISR Logic to record drop time
void record();
void record2();
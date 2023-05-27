/*
  Function prototypes for Alarm.cpp
*/
#define TRUE 1
#define FALSE 0

extern int AlarmActive;
extern int dangerAlarm;
extern int warningAlarm;
extern int calibrate;
//  Logic to control alarm states
void AlarmTask();
void blink(unsigned long period_ms);
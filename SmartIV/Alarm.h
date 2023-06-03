/*
  Function prototypes for Alarm.cpp
*/
#define TRUE 1
#define FALSE 0

#define WARN_AND_CALIBRATE_LED_PIN 4 // yellow
#define DANGER_LED_PIN 5  // red
extern int AlarmActive;
extern int dangerAlarm;
extern int warningAlarm;
extern int calibrate;
//  Logic to control alarm states
void AlarmTask();
void blink(int pin, unsigned long period_ms);
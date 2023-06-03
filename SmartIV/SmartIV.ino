// /*
//   Main control loop for IV Monitoring System with Smart Sampling Rate
// */
#include <avr/dtostrf.h>
#include "Sensors.h"
#include "Alarm.h"
#include "DataLog.h"
#include "Compute.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 1
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
#define BAUD_RATE 9600

// Variables to control for flow rate monitoring
int calibrateDropCount;
int dropCount;
int dropSensed;
int missedDropCount;
int consecutiveMissedDropCount;
unsigned long oldDropTime;
unsigned long newDropTime;
unsigned long oldDeltaT;
unsigned long newDeltaT;
unsigned long turnOnTime;
int deltaTBound;
unsigned long totalVolume;
unsigned long missedVolume;
int dangerAlarm;
int warningAlarm;

// Flags for each task
int SensorsActive;
int ComputeActive;
int DataLogActive;
int DisplayActive;
int AlarmActive;

// Variable to keep track of sensor configuration
int SensorsState;
unsigned long prevTime;
float flowRate;

// Parameters and variables for 
// SOFTWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 100;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
#define	BUF_SIZE	75
char curMessage[BUF_SIZE] = { "Hello! This is old message?" };
char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
bool newMessageAvailable = true;

void setup() {

  // delay(5000);
  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

  // default values for global variables
  SensorsActive = 1;
  ComputeActive = 0;
  DataLogActive = 0;
  DisplayActive = 1;
  AlarmActive = 0;

  dropSensed = FALSE;
  SensorsState = TRUE;
  calibrateDropCount = 0;
  dropCount = 0;
  missedDropCount = 0;
  consecutiveMissedDropCount = 0;
  oldDropTime = 0;
  newDropTime = 0;
  oldDeltaT = 180000;
  newDeltaT = 0;
  deltaTBound = 2000;

  totalVolume = 0;
  missedVolume = 0;
  SensorsState = 1;

  dangerAlarm = FALSE;
  warningAlarm = FALSE;

  prevTime = 0;
  flowRate = 0.0;

  // set appropriate input/output config for sensor pins
  pinMode(TOP_SENSOR_POWER_PIN, OUTPUT);
  pinMode(TOP_SENSOR_OUTPUT_PIN, INPUT_PULLUP);
  pinMode(BOT_SENSOR_POWER_PIN, OUTPUT);
  pinMode(BOT_SENSOR_OUTPUT_PIN, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  
  // set appropriate input/output config for sensor pins
  // pinMode(WARN_AND_CALIBRATE_LED_PIN, OUTPUT);
  // pinMode(DANGER_LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(TOP_SENSOR_OUTPUT_PIN), record, RISING);
  attachInterrupt(digitalPinToInterrupt(BOT_SENSOR_OUTPUT_PIN), record, RISING);

  digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
  digitalWrite(BOT_SENSOR_POWER_PIN, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);

  // Initialize serial port with desired baud rate
  Serial.begin(BAUD_RATE);
  // delay(2000);
}
unsigned long old = 0;
void loop() {
  if (SensorsActive) {
    SensorsTask();
  }

  if (ComputeActive) {
    ComputeTask();
  }

  // if (AlarmActive) {
  //   AlarmTask();
  // }

  if (SensorsState == FALSE) {
    unsigned long currTime = millis();
    // timer behavior that controls the turning on of sensor pairs
    // if time elapsed is greater than the old delta t - 2 seconds, then turn back on
    if (currTime - oldDropTime >= (oldDeltaT - deltaTBound - DEBOUNCE_DELAY)) {
      noInterrupts();
      digitalWrite(TOP_SENSOR_POWER_PIN, HIGH);
      digitalWrite(BOT_SENSOR_POWER_PIN, HIGH);
      interrupts();
      delay(DEBOUNCE_DELAY);
      dropSensed = FALSE;
      SensorsState = TRUE;
      turnOnTime = millis();
    }
  }

  if (DisplayActive) {
    flowRate = 3600.0 / (oldDeltaT * GTT / 1000);
    dtostrf(flowRate, 6, 2, curMessage);
    newMessageAvailable = TRUE;
  }

  // newMessage
  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      // Serial.println(curMessage);
      newMessageAvailable = FALSE;
      DisplayActive = FALSE;
    }
    P.displayReset();
  }
}
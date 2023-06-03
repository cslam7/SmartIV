// /*
//   Function prototypes for Display.c
// */

// #ifndef DISPLAY_H_
// #define DISPLAY_H_
// #include <Arduino.h>
// #include <MD_Parola.h>
// #include <MD_MAX72xx.h>
// #include <SPI.h>

// #define TRUE 1
// #define FALSE 0
// extern int DisplayActive;
// extern int dropCount;
// extern unsigned long oldDropTime;
// extern unsigned long newDropTime;
// extern unsigned long oldDeltaT;
// extern unsigned long newDeltaT;
// extern unsigned long flowRate;
// extern MD_Parola P;


// #include <MD_Parola.h>
// #include <MD_MAX72xx.h>
// #include <SPI.h>
// // Define the number of devices we have in the chain and the hardware interface
// // NOTE: These pin numbers will probably not work with your hardware and may
// // need to be adapted
// #define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
// #define MAX_DEVICES 11
// #define CLK_PIN   13
// #define DATA_PIN  11
// #define CS_PIN    10

// #define PRINT(s, x)
// #define PRINTS(x)
// #define PRINTX(x)

// //  Logic to control LEDS for flow rate display
// void DisplayTask();

// #endif  //  DISPLAY_H_
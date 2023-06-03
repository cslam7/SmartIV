// /*
//   All code related to interfacing with the optical sensors
//   and corresponding control logic
// */

// #include "Display.h"

// // Global message buffers shared by Serial and Scrolling functions
// #define	BUF_SIZE	75
// char curMessage[BUF_SIZE] = { "" };
// char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
// bool newMessageAvailable = true;
// extern int DisplayActive;

// // uint8_t scrollSpeed = 100;    // default frame delay value
// // textEffect_t scrollEffect = PA_SCROLL_LEFT;
// // textPosition_t scrollAlign = PA_LEFT;
// // uint16_t scrollPause = 2000; // in milliseconds
// void DisplayTask() {
//   Serial.println("Entering disply task");
//   uint8_t scrollSpeed = 100;    // default frame delay value
//   textEffect_t scrollEffect = PA_SCROLL_LEFT;
//   textPosition_t scrollAlign = PA_LEFT;
//   uint16_t scrollPause = 2000; // in milliseconds
//   P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
//   if (P.displayAnimate())
//   {
//     Serial.println("Entering display animate");
//     if (newMessageAvailable)
//     {
//       // strcpy(curMessage, newMessage);
//       flowRate = 12.43;
//       sprintf(curMessage, "%.2f", flowRate);
//       Serial.println("I should be displaying");
//       // newMessageAvailable = false;
      
//     }
//     P.displayReset();
//   }
//   DisplayActive = FALSE;
// }

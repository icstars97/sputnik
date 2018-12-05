#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL



void RTC_Init(); // real time clock init



void RTC_LoadValue(uint32_t preload); // set real time clock main counter preload 


uint32_t RTC_GetTime(); // get value of real time clock main counter
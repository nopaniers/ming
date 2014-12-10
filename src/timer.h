//------------------------------------------------------------------------------
// Timer
//------------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

#include "types.h"

//------------------------------------------------------------------------------
// Memory layout
//------------------------------------------------------------------------------

// Base address
#define TIMER     0xff003000

// Offsets
#define TIME_LOW        0x00
#define TIME_HIGH       0x04
#define ALARM_LOW       0x08
#define ALARM_HIGH      0x0c
#define CLEAR_INTERRUPT 0x10
#define CLEAR_ALARM     0x14


typedef struct Timer_S {
  uint64  time;
  uint64  alarm;
  uint32 *clear_time;
  uint32 *clear_alarm;
} *Timer;

static Timer timer;


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

uint64 get_time();


#endif

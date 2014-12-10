//------------------------------------------------------------------------------
// Timer
//------------------------------------------------------------------------------

#include "timer.h"

typedef struct Time_S {
  int16 year;     // Negative for BC, positive for AD
  uint8 month;
  uint8 day;
  uint8 hour;
  uint8 minute;
  uint8 second;
} *Time;

static Timer timer = (Timer) TIMER;


uint64 
get_time()
{
  return timer->time;
}

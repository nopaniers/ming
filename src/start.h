//==============================================================================
// start.h
//==============================================================================

#ifndef START_H
#define START_H

#include "types.h"

//------------------------------------------------------------------------------
// Constants about architecture
//------------------------------------------------------------------------------

// Useful addresses in memory
#define SERIAL_ADDRESS 0xff002000
#define ARM_BASE 0x8000

//
// Common addresses
//
// Found from boot logs. In future these should be discovered dynamically.

#define INTERRUPT_CONTROLLER 0xff000000
#define DEVICE_BUS 0xff001000

#define RTC        0xff010000
#define TTY1       0xff002000
#define TTY2       0xff011000
#define TTY3       0xff012000
#define SMC91X     0xff013000

#define AUDIO      0xff004000
#define MEM_LOG    0xff006000
#define BATTERY    0xff015000
#define EVENTS     0xff016000
#define NAND       0xff017000
#define QEMU_PIPE  0xff018000
#define SWITCH1    0xff01a000
#define SWITCH2    0xff01b000

// The corresponding interrupts
#define INTERRUPT_CONTROLLER_IRQ -1
#define DEVICE_BUS_IRQ 1
#define TIMER_IRQ      3
#define RTC_IRQ       10
#define TTY1_IRQ       4
#define TTY2_IRQ      11
#define TTY3_IRQ      12
#define SMC91X_IRQ    13
#define AUDIO_IRQ     15
#define MEM_LOG_IRQ   -1
#define BATTERY_IRQ   16
#define EVENTS_IRQ    17
#define NAND_IRQ      -1
#define QEMU_PIPE_IRQ 18
#define SWITCH1_IRQ   19
#define SWITCH2_IRQ   20


//------------------------------------------------------------------------------
// Function Prototypes from start.s
//------------------------------------------------------------------------------

// Writing to an arbitrary address
void putc_memory(unsigned int address, unsigned character);
void word_copy(uint32 *from, uint32 *to, uint32 number_of_bytes);

void writeln_memory(unsigned int address, char *string);



// Writing to the serial port
void writeln_serial(char *string);

// Hang in infinite loop
void hang();

// Memset, currently taken from Apple
void *memset(void *ptr, int c, unsigned len);


#endif

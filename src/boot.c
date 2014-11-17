//-------------------------------------------------------------------------
// Ming Operating System
//-------------------------------------------------------------------------

#include "start.h"


//------------------------------------------------------------------------------
// Writing to serial port
//------------------------------------------------------------------------------

void
show_welcome(unsigned zero, unsigned type, unsigned tags)
{
  writeln_serial("");
  writeln_serial("---------------------");
  writeln_serial("Ming OS, version 0.01");
  writeln_serial("---------------------");
  writeln_serial("");
  writeln_serial("Written by Charles Hill, 2014");
  writeln_serial("");
}

static unsigned char* video_buffer = (unsigned char *) 0x100000;

void
splash_screen()
{
  writeln_serial("Setting up the splash screen.");

  memset(video_buffer, 0x1a, WIDTH * HEIGHT);
  memset(video_buffer+WIDTH*HEIGHT, 0xaa, WIDTH * HEIGHT);


  int width = *((int *) 0xff014000);
  if (width==WIDTH) {
    writeln_serial("Got the right screen width.");
  }

  int height= *((int *) 0xff014004);
  if (height==HEIGHT) {
    writeln_serial("Got the right screen height.");
  }

  // Blit to screen
  *((int *) 0xff014010) = 0x100000;

  writeln_serial("Finished setting up splash screen.");
  hang();
}


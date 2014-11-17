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


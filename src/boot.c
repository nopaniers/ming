//-------------------------------------------------------------------------
// Ming Operating System
//-------------------------------------------------------------------------

#include "start.h"
#include "types.h"


//------------------------------------------------------------------------------
// Booting sequence functions
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


void
copy_vectors_to_address_zero()
{
  extern uint32 vectors_begin;
  writeln_serial("Copying vectors");  
  word_copy(&vectors_begin, 0, 32);
  writeln_serial("Finished copying vectors");
}



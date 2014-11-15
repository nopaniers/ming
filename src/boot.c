//-------------------------------------------------------------------------
// Ming Operating System
//-------------------------------------------------------------------------

// Useful addresses in memory
#define SERIAL_ADDRESS 0xff002000
#define VIDEO_ADDRESS 0xabe01000
#define ARM_BASE 0x8000

// Size of the screen
#define WIDTH 800
#define HEIGHT 1280


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

extern void put_char(unsigned int, unsigned int);
extern void hang();


//------------------------------------------------------------------------------
// Writing to serial port
//------------------------------------------------------------------------------

void 
write_char(char a) 
{
  put_char(SERIAL_ADDRESS, a);
}


void 
writeln(char* str) 
{
  char nextChar;
  while (nextChar = *str) {
    put_char(SERIAL_ADDRESS, nextChar);
    str++;
  }
  put_char(SERIAL_ADDRESS, '\n');
}


int 
show_welcome(unsigned zero, unsigned type, unsigned tags)
{
  writeln("");
  writeln("---------------------");
  writeln("Ming OS, version 0.01");
  writeln("---------------------");
  writeln("");
  writeln("Written by Charles Hill, 2014");
  writeln("");

  hang();

  return 0;
}


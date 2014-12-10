//------------------------------------------------------------------------------
// Video functions
//------------------------------------------------------------------------------

#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"


//------------------------------------------------------------------------------
// Memory layout
//------------------------------------------------------------------------------

#define VIDEO        0xff014000

#define GET_WIDTH           0x00
#define GET_HEIGHT          0x04
#define INTERRUPT_STATUS    0x08
#define INTERRUPT_ENABLE    0x0c
#define SET_BASE            0x10
#define SET_ROTATION        0x14
#define SET_BLANK           0x18
#define GET_PHYSICAL_WIDTH  0x1c
#define GET_PHYSICAL_HEIGHT 0x20
#define GET_FORMAT          0x24

#define FB_IRQ                14


// static unsigned char* video_buffer = (unsigned char *) VIDEO_BUFFER;


//------------------------------------------------------------------------------
// Video structure
//------------------------------------------------------------------------------

typedef enum {
  brga   = 0x01, // All values 8 bits for each colour except:
  rgbx   = 0x02,
  rgb    = 0x03,
  rgb565 = 0x04, // 5, 6, 5 bits (default)
  bgra   = 0x05,
  rgba   = 0x06, // 5, 5, 5, 1 bits
  rgba4  = 0x08, // 4, 4, 4, 4 bits
} VideoFormat;


typedef struct Video_S 
{
  uint32  width;
  uint32  height;
  uint32  interrupt_status;
  uint32  interrupt_enabled;
  uint32 *base;
  uint32  rotation;
  uint32  set_blank;
  uint32  physical_width;
  uint32  physical_height;
  VideoFormat format;
} *Video;

static Video video;


//------------------------------------------------------------------------------
// Colours
//------------------------------------------------------------------------------

#define BLUE  0x1a
#define RED   0xaa
#define WHITE 0xff
#define BLACK 0x00


//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

void splash_screen();



#endif

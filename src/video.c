//------------------------------------------------------------------------------
// Video
//------------------------------------------------------------------------------

#include "video.h"
#include "start.h"

static Video video = (Video) VIDEO;

void
splash_screen_c()
{
  extern uint32 ming_logo;
  writeln_serial("Setting up the splash screen.");

  // Blit to screen
  video->base = &ming_logo;
  
  writeln_serial("Finished setting up splash screen.");
}

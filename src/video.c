//------------------------------------------------------------------------------
// Video
//------------------------------------------------------------------------------

#include "video.h"
#include "start.h"

static Video video = (Video) VIDEO;


void
splash_screen()
{
  writeln_serial("Setting up the splash screen.");

  unsigned half_screen = WIDTH*HEIGHT;
  memset(video_buffer, BLUE, half_screen);
  memset(video_buffer + half_screen, RED, half_screen);
 
  if (video->width==WIDTH) {
    writeln_serial("Got the right screen width.");
  }

  if (video->height==HEIGHT) {
    writeln_serial("Got the right screen height.");
  }

  // Blit to screen
  video->base = VIDEO_BUFFER;

  writeln_serial("Finished setting up splash screen.");
  hang();
}

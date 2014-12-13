//------------------------------------------------------------------------------
// Video
//------------------------------------------------------------------------------

#![no_std]
#![allow(improper_ctypes)]

#![feature(lang_items)]
#[lang = "sized"]
trait Sized {}

#[lang = "sync"]

/*------------------------------------------------------------------------------
 * Video data structure
 *------------------------------------------------------------------------------
 *
 * The screen is mapped directly to a memory location in the Android
 * emulator. This structure reflects that layout in memory.
 *
 *----------------------------------------------------------------------------*/

struct Video 
{
  width: u32,
  height: u32,
  interrupt_status: u32,
  interrupt_enabled: u32,
  base: &'static u32,
  rotation: u32,
  set_blank: u32,
  physical_width: u32,
  physical_height: u32,
  format: u32
}

static VIDEO: *mut Video = 0xff014000 as *mut Video;


/*------------------------------------------------------------------------------
 * Display splash screen
 *----------------------------------------------------------------------------*/

#[no_mangle]
#[no_stack_check]
pub fn splash_screen()
{
   // A raw splash screen is included in the kernel image. 
   // ming-logo refers to the first byte in memory of that image.
   extern { static ming_logo: u32; }

   // Blit ming-logo to the screen
   unsafe { 
      (*VIDEO).base = &ming_logo;
   }
}

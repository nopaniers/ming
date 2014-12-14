//-------------------------------------------------------------------------
// Ming Operating System
//-------------------------------------------------------------------------

#![no_std]
#![feature(globs)]
// #![feature(lang_items)]

extern crate core;

use serial::*;

mod serial;


//------------------------------------------------------------------------------
// Booting sequence functions
//------------------------------------------------------------------------------

#[no_mangle]
#[no_stack_check]
pub fn show_welcome()
{
  writeln_serial("");
  writeln_serial("---------------------");
  writeln_serial("Ming OS, version 0.01");
  writeln_serial("---------------------");
  writeln_serial("");
  writeln_serial("Written by Charles Hill, 2014");
  writeln_serial("");
}




#[no_mangle]
#[no_stack_check]
pub fn copy_vectors_to_address_zero()
{
   // When the Android emulator boots up, memory starts at location
   // 0x10000.  However, the vector interrupt table *should* be
   // located at 0x00000 for exceptions and interrupts to work
   // properly.  This routine copies the vector table to the right
   // place.

   writeln_serial("Copying vectors");
   
   // These functions/locations are defined in start.s
   extern { 
      static vectors_begin: u32;
      fn word_copy(src: *const u32, dest: *mut u32, length: u32);
   }

   // Actually do the copy: just a direct memory copy
   unsafe {
      word_copy(&vectors_begin, 0x0 as *mut u32, 32);
   }

   writeln_serial("Finished copying vectors");
}



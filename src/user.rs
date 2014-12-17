//-------------------------------------------------------------------------
// Ming Operating System
//-------------------------------------------------------------------------

// #![no_std]
// #![feature(globs)]
// #![feature(lang_items)]

extern crate core;

use serial::*;

// mod serial;


//------------------------------------------------------------------------------
// User mode functions
//------------------------------------------------------------------------------

#[no_mangle]
#[no_stack_check]
pub fn user_mode_function()
{
  writeln_serial("");
  writeln_serial("Switched to user mode");
  writeln_serial("");
}


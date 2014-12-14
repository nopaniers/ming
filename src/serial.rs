//==============================================================================
// Hello
//==============================================================================

#![no_std]
#![feature(globs)]
#![feature(lang_items)]

extern crate core;
use core::str::*;


/*------------------------------------------------------------------------------
 * Serial Device Data Structure
 *------------------------------------------------------------------------------
 *
 * The serial device is communicated with via memory, as set out in
 * this data structure.
 *
 *----------------------------------------------------------------------------*/

struct SerialPort
{
   put_char: u32,
   bytes_ready: u32,
   cmd: u32,
   data_ptr: &'static u32,
   data_len: u32
}

static SERIAL_PORT: *mut SerialPort = 0xff002000 as *mut SerialPort;


/*------------------------------------------------------------------------------
 * Writing to the serial port
 *----------------------------------------------------------------------------*/

#[no_stack_check]
pub fn write_char(c: char)
{
   unsafe {
      (*SERIAL_PORT).put_char = c as u32;
   }
}


#[no_mangle]
#[no_stack_check]
pub fn writeln_serial(message: &str)
{
   for c in message.chars() {
      write_char(c);
   }
   write_char('\n');
}

//==============================================================================
// Serial Device
//==============================================================================

// #![no_std]
// #![feature(globs)]
// #![feature(lang_items)]

extern crate core;
use core::str::*;
// use core::intrinsics::volatile_load;


/*------------------------------------------------------------------------------
 * Serial Device Data Structure
 *------------------------------------------------------------------------------
 *
 * The serial device is communicated with via memory, as set out in
 * this data structure.
 *
 *----------------------------------------------------------------------------*/

#[allow(dead_code)]
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

#[no_mangle]
#[no_stack_check]
pub fn write_char(c: char)
{
   unsafe {
      // There should probably be a check here in a read device.
      // while volatile_load(&(*SERIAL_PORT).bytes_ready)==0 {}

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



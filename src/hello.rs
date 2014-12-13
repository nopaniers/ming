//==============================================================================
// Hello
//==============================================================================

#![no_std]
#![allow(improper_ctypes)]

#![feature(lang_items)]
#[lang = "sized"]
trait Sized {}

#[no_mangle]
#[no_stack_check]
pub fn hello_rust() 
{
   // Write a single character to the serial output
   unsafe {
      *(0xff002000 as *mut u16) = 'R' as u16;
   }
}

//------------------------------------------------------------------------------
// Compiler functions
//------------------------------------------------------------------------------

use serial::*;

// These functions and traits are used by the compiler. These are
// normally provided by libstd, but we don't have that in a bare metal
// implementation

#[lang = "stack_exhausted"] 
extern fn stack_exhausted()
{ 
  writeln_serial("Stack exhausted!"); 
  loop {} 
}


#[lang = "eh_personality"] extern fn eh_personality() 
{
   writeln_serial("Stack exhausted!");
   loop {}
}

#[lang = "panic_fmt"] 
fn panic_fmt() -> ! { loop {} }

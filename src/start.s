//------------------------------------------------------------------------------
// Ming OS
//
// Start up the operating system
//------------------------------------------------------------------------------
	
.globl _start
_start:				// Control passes here from the bootloader
	mov sp, #0x10000	// Set up the stack
	bl show_welcome

	
.globl hang
hang:				// This is for debugging purposes: stop
	b hang			// Loop forever


.globl put_char
put_char:
	str r1, [r0]
	bx lr			


//------------------------------------------------------------------------------
// Ming OS
//
// Start up the operating system
//------------------------------------------------------------------------------
	
.globl _start
_start:				// Control passes here from the bootloader
	mov sp, #0x10000	// Set up the stack
	blx show_welcome
	blx splash_screen
	blx hang

	
.globl hang
hang:				// This is here for debugging purposes
	b hang			// Loop forever


.globl putc_memory
putc_memory:			// r0: address to print to,
				// r1: character to print
	str 	r1, [r0]
	bx 	lr

	
.globl writeln_serial
.globl writeln_memory
writeln_serial: 		// Write a string to the serial port
	mov	r1, r0		// r1 now contains the string address
	mov	r0, #0x2000 	// The serial port address
	movt	r0, #0xff00
writeln_memory:
	ldrb	r2, [r1]	// Load first character
	cmp	r2, #0
	beq	.L_end_string	// Jump out if we're passed the empty string
.L_loopy:		
	str	r2, [r0]	// Write character to serial port address
	ldrb	r2, [r1, #1]!	// Next character
	cmp	r2, #0
	bne	.L_loopy
.L_end_string:
	movs	r2, #10		// Newline
	str	r2, [r0]	
	bx	lr


//------------------------------------------------------------------------------
// Ming OS
//
// Start up the operating system
//------------------------------------------------------------------------------

.text
	
.arm	
.align 2

.globl vectors_begin
.globl vectors_end
.globl _start
vectors_begin:
	ldr pc, reset_address
	ldr pc, undefined_instruction_address
	ldr pc, swi_address
	ldr pc, prefetch_abort_address
	ldr pc, data_abort_address
	ldr pc, not_used_address
	ldr pc, irq_address
	ldr pc, firq_address


reset_address:			.word _start
undefined_instruction_address: 	.word undefined_handler
swi_address:			.word swi_handler
prefetch_abort_address:		.word prefetch_handler
data_abort_address:		.word data_abort_handler
not_used_address:		.word not_used_handler
irq_address:			.word irq_handler
firq_address:			.word fiq_handler

vectors_end:	
	
_start:				// Control passes here from the bootloader
	ldr 	sp, =0x07FFFFF0	// Set up the stack (at the end of 128MB)
	bl 	show_welcome
	bl 	copy_vectors_to_address_zero
	bl 	splash_screen
	bl 	switch_into_user_mode
	bl 	hang
	

.globl switch_into_user_mode
switch_into_user_mode:
	mov 	ip, sp		// Setting up the user mode stack
	msr 	CPSR_c, #0xdf 	// System mode (ie. user with super privilege)
	mov 	sp, ip		// Set up stack
	msr 	CPSR_c, 0xd3
	
	mov 	r0, #0x10 	// User mode
	msr 	SPSR, r0  	// Set the status register next time we movs
	ldr 	lr, =user_mode_function
	movs	pc, lr		// Call the function and change to user mode
	
	
.globl hang
hang:				// This is here for debugging purposes
	b 	hang		// Loop forever

	
.globl word_copy
word_copy:
	ldr 	r3, [r1], #4
	str 	r3, [r0], #4
	subs 	r2, r2, #4
	bge 	word_copy
	bx	lr
	
.globl putc_memory
putc_memory:			// r0: address to print to,
				// r1: character to print
	str 	r1, [r0]
	bx 	lr

	
.globl writeln_serial_asm
.globl writeln_memory
writeln_serial_asm: 		// Write a string to the serial port
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



undefined_handler:
swi_handler:	
prefetch_handler:	
data_abort_handler:	
not_used_handler:	
irq_handler:	
fiq_handler:	

.data

.global ming_logo
ming_logo:
	.incbin "../resources/ming_logo2.raw"

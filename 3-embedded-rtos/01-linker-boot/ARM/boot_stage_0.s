	.syntax unified
	.cpu cortex-m4
	.thumb

/* Minimal interrupt vector table. Only the stack pointer and reset handler */
	.section .isr_vector
	.global __Vectors
__Vectors:
	.word  _stack_top
	.word  Reset_Handler

/* Reset vector. */
	.section .text
	.global Reset_Handler
	.type  Reset_Handler, %function
Reset_Handler:
	/* Copy .data from FLASH to RAM */
	ldr  r0, =_data
	ldr  r1, =_edata
	ldr  r2, =_etext
	cmp  r0, r1
	beq  nodata
dataloop:
	ldr  r3, [r2], #4
	str  r3, [r0], #4
	cmp  r1, r0
	bne  dataloop
nodata:
	/* Zero .bss */
	ldr  r0, =_bss_start
	ldr  r1, =_bss_end
	cmp  r0, r1
	beq  nobss
	movs r3, #0
bssloop:
	str  r3, [r0], #4
	cmp  r1, r0
	bne  bssloop
nobss:
	/* Call global contructors for C++ */
	/* Can't use r0-r3 as the callee doesn't preserve them */
	ldr  r4, =__init_array_start
	ldr  r5, =__init_array_end
	cmp  r4, r5
	beq  noctor
ctorloop:
	ldr  r3, [r4], #4
	blx  r3
	cmp  r5, r4
	bne  ctorloop
noctor:
	/* Continue the boot process in C++ */
	/* _Z11kernel_bootv is the C++ mangled name of function kernel_boot */
	bl   _Z11kernel_bootv
	.size	Reset_Handler, .-Reset_Handler

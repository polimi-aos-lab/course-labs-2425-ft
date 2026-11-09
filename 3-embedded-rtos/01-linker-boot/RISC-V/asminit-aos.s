	.section .isr_vector
	.global __Vectors
__Vectors:
	.option push
	.option norvc /* Disable instruction compression here */
	j    Reset_Handler
	.option pop

	.section .text
	.global Reset_Handler
	.type Reset_Handler, %function
Reset_Handler:
	.option push
	.option norelax /* Disable global pointer relaxation here */
	la   gp,      __global_pointer$
	.option pop
	la   sp, _stack_top
	/* Copy .data from FLASH to RAM */
	la   t0, _data
	la   t1, _edata
	la   a0, _etext
dataloop:
	beq  t0, t1, dataend
	lw   a1, 0(a0)
	addi a0, a0, 4
	sw   a1, 0(t0)
	addi t0, t0, 4
	j    dataloop
dataend:
	/* Zero .bss */
	la   t0, _bss_start
	la   t1, _bss_end
bssloop:
	beq  t0, t1, bssend
	sw   zero, 0(t0)
	addi t0, t0, 4
	j    bssloop
bssend:
	/* Call global constructors in C++ */
	/* Can't use temporaries here */
	la   s0, __init_array_start
	la   s1, __init_array_end
ctorloop:
	beq  s0, s1, ctorend
	lw   t0, 0(s0)
	addi s0, s0, 4
	jalr t0
	j    ctorloop
ctorend:
	/* Continue the boot process in C++ */
	j    kernel_boot
	.size Reset_Handler, .-Reset_Handler

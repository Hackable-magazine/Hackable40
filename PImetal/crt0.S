	.section .text.boot
	.global __start
	.type	__start, %function

__start:
	# get cpuid, move slaves to loop
	mrs	x7, mpidr_el1
	and	x7, x7, #3
	cbz	x7, __start_master
0:	wfe
	b	0b  // jump to 0 backward

__start_master:
	# Load stack pointer
	ldr	x2, =__stack_start
	mov	sp, x2

	# Clear BSS
	ldr	w0, =__bss_start
	ldr	w1, =__bss_size
1:	cbz	x1, 2f  // jump 1 forward
	str	xzr, [x0], #8
	sub	x1, x1, #1
	cbnz	x1, 1b
2:
	bl	kernelmain	// Call main
	b	0b	// loop forever

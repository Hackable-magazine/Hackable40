MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000, LENGTH = 0x10000000
}

SECTIONS
{
  /* . = 0x80000; */
  .text : { *(.text .text.*) }
  .rodata : { *(.rodata .rodata.*) }
  /*
  .ARM.extab   : { *(.ARM.extab*) }
  PROVIDE_HIDDEN (__exidx_start = .);
  .ARM.exidx   : { *(.ARM.exidx*) }
  PROVIDE_HIDDEN (__exidx_end = .);
  */
  .data : { *(.data .data.*) }

  .bss (NOLOAD):
  {
   __bss_start = ALIGN(0x10);
   *(.bss .bss.*)
   __bss_end = ALIGN(0x10);
  }
  __end = .;

  . = ALIGN(0x10);
  . += 0x1000;
  __stack_start = .;

  /DISCARD/ :
  {
   *(.comment) *(.gnu*)
   *(.note*) *(.eh_frame*)
  }
}

__bss_size = (__bss_end - __bss_start) >> 3;


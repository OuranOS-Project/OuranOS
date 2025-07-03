ENTRY(_start)

SECTIONS
{
  . = 0x1000;

  .text : {
    *(.text._start)  /* Placer _start en premier */
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data)
  }

  .bss : {
    *(COMMON)
    *(.bss)
  }
}
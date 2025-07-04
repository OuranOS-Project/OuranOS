[bits 32]

extern keyboard_handler

global isr33

isr33:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call keyboard_handler

    pop gs
    pop fs
    pop es
    pop ds
    popa

    iretd
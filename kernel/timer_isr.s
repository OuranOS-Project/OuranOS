[bits 32]

extern timer_handler

global isr32

isr32:
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

    call timer_handler

    pop gs
    pop fs
    pop es
    pop ds
    popa

    ; Envoyer EOI au PIC
    mov al, 0x20
    out 0x20, al

    iretd

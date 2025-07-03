[bits 32]

extern idtp
extern fault_handler

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global idt_load

isr0:
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

    push dword 0
    push dword 0
    call fault_handler
    add esp, 8

    pop gs
    pop fs
    pop es
    pop ds
    popa

    cli
    hlt
    jmp $

idt_load:
    lidt [idtp]
    ret

%macro ISR_NOERR 1
%if %1 != 0
isr%1:
    cli
    hlt
    jmp $
%endif
%endmacro

%assign i 0
%rep 32
    ISR_NOERR i
    %assign i i+1
%endrep


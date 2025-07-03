[bits 16]                              ; 16-bit code
org 0x7C00                             ; Boot sector starts at 0x7C00

gdt_start:
    dw 0x0                             ; Null descriptor
    dw 0x0 

gdt_code:
    dw 0xFFFF                          ; Limit
    dw 0x0                             ; Base low
    db 0x0                             ; Base middle
    db 10011010b                       ; Access byte (present, ring 0, code segment)
    db 11001111b                       ; Flags (4K granularity, 32-bit)
    db 0x0                             ; Base high

gdt_data:
    dw 0xFFFF                          ; Limit
    dw 0x0                             ; Base low
    db 0x0                             ; Base middle
    db 10010010b                       ; Access byte (present, ring 0, data segment)
    db 11001111b                       ; Flags (4K granularity, 32-bit)
    db 0x0                             ; Base high

gdt_end:
    dw 0x0                             ; End of GDT

gdt_descriptor:
    dw gdt_end - gdt_start - 1         ; Size of GDT
    dd gdt_start                       ; Address of GDT

cli                                    ; Clear interrupts
lgdt [gdt_descriptor]                  ; Load GDT

mov eax, cr0                           ; Read CR0
or eax, 0x1                            ; Set PE bit (Protected Mode Enable)
mov cr0, eax                           ; Write back to CR0

jmp 0x08:protected_mode_start          ; Jump to protected mode code

[bits 32]                              ; Switch to 32-bit mode
protected_mode_start:
    mov ax, 0x10                       ; Load data segment selector
    mov ds, ax                         ; Set DS
    mov es, ax                         ; Set ES
    mov fs, ax                         ; Set FS
    mov gs, ax                         ; Set GS
    mov ss, ax                         ; Set SS




times 510 - ($ - $$) db 0              ; Fill the rest of the sector with zeros
dw 0xAA55                              ; Boot signature 2 bytes
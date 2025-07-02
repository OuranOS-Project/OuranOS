bits 16 ; 16-bit code
org 0x7C00 ; Boot sector starts at 0x7C00

mov si, 0 

print:
    mov ah , 0x0E ; BIOS teletype output function
    mov al, [hello + si] ; Load character from string
    int 0x10 ; BIOS interrupt to print character
    add si, 1 ; Move to next character
    cmp byte [hello + si], 0 ; Check for null terminator
    jne print ; If not null, continue printing

jmp $

hello:
    db 'Hello, World!', 0 ; Null-terminated string


times 510 - ($ - $$) db 0 ; Fill the rest of the sector with zeros

dw 0xAA55  ; Boot signature 2 bytes
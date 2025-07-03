[bits 16]                              ; 16-bit code
org 0x7C00                             ; Boot sector starts at 0x7C00

start:

    mov si, boot
    call print_string                      ; Print boot message
    
    mov bx, 0x1000                         ; Load at address 0x1000
    mov dl , 0x00                          ; Use drive 0 (floppy)
    mov ah, 0x02                           ; Function to read sectors
    mov al, 16                             ; Tell the bios how many sectors to read
    mov cl, 0x02                           ; Sector 2 
    mov ch, 0                              ; Cylinder 0
    mov dh, 0                              ; Head 0
    int 0x13                               ; Read sectors from disk
    jc disk_error                          ; If error, jump to error handler
 
    cli                                    ; Clear interrupts
    lgdt [gdt_descriptor]                  ; Load GDT

    mov eax, cr0                           ; Read CR0
    or eax, 0x1                            ; Set PE bit (Protected Mode Enable)
    mov cr0, eax                           ; Write back to CR0

    jmp 0x08:protected_mode_start          ; Far jump to switch to protected mode


print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

disk_error:
    mov si, error_msg
    call print_string
    jmp $

; Messages
boot db 'Booting...', 0x0D, 0x0A, 0
error_msg db 'Disk error', 0x0D, 0x0A, 0

gdt_start:
    dq 0                ; Null descriptor

gdt_code:
    dw 0xFFFF           ; Limit (0-15)
    dw 0x0000           ; Base (0-15)
    db 0x00             ; Base (16-23)
    db 10011010b        ; Present, DPL 0, Code, Exec/Read
    db 11001111b        ; 4K granularity, 32-bit, Limit (16-19)
    db 0x00             ; Base (24-31)

gdt_data:
    dw 0xFFFF           ; Limit (0-15)
    dw 0x0000           ; Base (0-15)
    db 0x00             ; Base (16-23)
    db 10010010b        ; Present, DPL 0, Data, Read/Write
    db 11001111b        ; 4K granularity, 32-bit, Limit (16-19)
    db 0x00             ; Base (24-31)

gdt_end:
    dw 0x0                             ; End of GDT

gdt_descriptor:
    dw gdt_end - gdt_start - 1         ; Size of GDT
    dd gdt_start                       ; Address of GDT

[bits 32]                              ; Switch to 32-bit mode
protected_mode_start:
    mov ax, 0x10                       ; Load data segment selector
    mov ds, ax                         ; Set DS
    mov es, ax                         ; Set ES
    mov fs, ax                         ; Set FS
    mov gs, ax                         ; Set GS
    mov ss, ax                         ; Set SS
    mov esp, 0x90000                   ; Set stack pointer

    jmp 0x08:0x1000                    ; Jump to the kernel code

times 510 - ($ - $$) db 0              ; Fill the rest of the sector with zeros
dw 0xAA55                              ; Boot signature 2 bytes
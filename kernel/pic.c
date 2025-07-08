#include "kernel.h"
#include "screen.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"
#include "input.h"
#include "timer.h"
#include "bitmap_font.h"
#include "string.h"
#include "debug.h"
#include "io.h"
#include "memory.h"
#include "terminal.h"

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)
#define ICW1_INIT       0x10
#define ICW1_ICW4       0x01
#define ICW4_8086       0x01

void pic_remap() {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, 0x20); // Remap PIC1 to 0x20-0x27
    outb(PIC2_DATA, 0x28); // Remap PIC2 to 0x28-0x2F
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
    // Autoriser IRQ0 (timer) et IRQ1 (clavier) uniquement
    outb(PIC1_DATA, 0xFC); // 11111100 : IRQ0 et IRQ1 activés
    outb(PIC2_DATA, 0xFF);
}
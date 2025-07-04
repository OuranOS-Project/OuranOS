#include "keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define PIC1_COMMAND 0x20
#define PIC_EOI 0x20

// Qwerty
static const char scancode_table[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x0
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   // 0x0E
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',           // 0x1C
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*',        // 0x28
    0, ' ', 0,                                                                // 0x36
};

// Azerty
static const char scancode_table_azerty[128] = {
    0,  27, '&', 'é', '"', '\'', '(', '-', 'è', '_', 'ç', 'à', ')', '=', '\b', // 0x0
    '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n',   // 0x0E
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '`',             // 0x1C
    0, '*', '<', 'w', 'x', ',', ';', ':', '=', '?', '/', 0, '*',               // 0x28
    0, ' ', 0,                                                                // 0x36
};


void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode & 0x80) {
    } else {
        char c = scancode_table_azerty[scancode];
        if (c) {
            screen_put_char((point_t){0, 0}, c);
        }
    }
    outb(PIC1_COMMAND, PIC_EOI);
}

void keyboard_init() {
    idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8E);
}
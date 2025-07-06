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


volatile keyboard_state_t keyboard_state = {0};


keyboard_state_t keyboard_scan() {
    return keyboard_state;
}

int keyboard_key_down(keyboard_state_t state, uint8_t scancode) {
    return state.keys[scancode];
}

/*-----------------------------------*/



#define KEYBOARD_DATA_PORT 0x60
#define PIC1_COMMAND 0x20
#define PIC_EOI 0x20

// Qwerty
const char scancode_table_qwerty[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x0
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   // 0x0E
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',           // 0x1C
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*',        // 0x28
    0, ' ', 0,                                                                // 0x36
};

// Azerty
const char scancode_table_azerty[128] = {
    0,  27, '&', '?', '"', '\'', '(', '-', '?', '_', '?', '?', ')', '=', '\b', // 0x0
    '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n',   // 0x0E
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '`',             // 0x1C
    0, '*', '<', 'w', 'x', ',', ';', ':', '=', '?', '/', 0, '*',               // 0x28
    0, ' ', 0,                                                                // 0x36
};


void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        // key released
        keyboard_state.keys[scancode & 0x7F] = 0;
    } else {
        // key pressed
        keyboard_state.keys[scancode] = 1;
    }

    // Envoie un accusé de réception à l'IRQ1
    outb(0x20, 0x20);
}

void keyboard_init() {
    memset((void*)&keyboard_state, 0, sizeof(keyboard_state));
    pic_remap();
    idt_init();
    enable_interrupts();
}
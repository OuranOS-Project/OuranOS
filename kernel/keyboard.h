#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "kernel.h"

#define KEYBOARD_DATA_PORT 0x60

extern void isr33(); // From keyboard_isr.s

void keyboard_init();
void keyboard_handler();

#endif
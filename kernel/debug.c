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

void debug_panic(const char *msg) {
    screen_clear();
    //screen_change_font(font8x8, 8, 8);
    screen_print((point_t){0, 0}, "!!! KERNEL PANIC !!!", true, 15);
    screen_print((point_t){0, 2}, msg, true, 15);

    while (1) {
        __asm__ volatile ("cli; hlt");
    }
}
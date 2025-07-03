#include "debug.h"

void debug_panic(const char *msg) {
    screen_clear();
    screen_print((point_t){0, 0}, "!!! KERNEL PANIC !!!");
    screen_print((point_t){0, 2}, msg);

    while (1) {
        __asm__ volatile ("cli; hlt");
    }
}
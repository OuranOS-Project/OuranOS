#include "screen.h"
#include "memory.h"
#include "string.h"
#include "debug.h"
#include "idt.h"

void _start() {
    screen_clear();

    screen_print((point_t){0,0}, "Welcome to OuranOS!");

    idt_init();
    
    volatile int test = 5;
    screen_print_dec((point_t){0,2}, test);
    volatile int test2 = test / 0;
    screen_print_dec((point_t){0,3}, test2);

    screen_print((point_t){0,4}, "Test finished");

    while (1) {}
}

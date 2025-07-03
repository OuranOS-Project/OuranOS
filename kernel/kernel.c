#include "screen.h"
#include "memory.h"
#include "string.h"
#include "debug.h"
#include "idt.h"

void _start() {
    screen_clear();

    screen_print((point_t){0,0}, "Welcome to OuranOS!");

    idt_init();
    
    int test = 5;
    int test2 = test / 0; // This will cause a division by zero exception

    screen_print_dec((point_t){0,2}, test);
    screen_print_dec((point_t){0,3}, test2); // This will not be executed due to the exception

    screen_print((point_t){0,4}, "Test finished");

    while (1) {}
}

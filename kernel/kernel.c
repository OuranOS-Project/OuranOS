#include "kernel.h"

void _start() {
        
    screen_clear();
    
    screen_print((point_t){0, 0}, "Welcome to OuranOS!");

    while (1) {}
}
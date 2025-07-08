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
#include "on_start.h"
#include "terminal.h"

void _start() {
    on_start();
    
    /*
    char* buffer[256];
    *buffer = screen_print_input_string((point_t){0, 0}, true, 15);

    screen_clear();
    screen_print((point_t){0, 0}, "You entered:", true, 15);
    screen_print((point_t){0, 1}, *buffer, true, 15);
    */


    terminal_input_to_command("echo Hello World");

    while (1){

    }

}



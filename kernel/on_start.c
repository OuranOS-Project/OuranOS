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

void on_start(){
    screen_change_font(font8x8, 8, 8);
    idt_init();
    pic_remap();
    keyboard_init();
    enable_interrupts();
    timer_init(1000);
}
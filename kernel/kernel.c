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

#define VIDEO_MEMORY ((uint8_t*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200


void _start() {
    screen_change_font(font8x8, 8, 8);
    idt_init();
    pic_remap();
    keyboard_init();
    enable_interrupts();
    timer_init(1000);

    //screen_draw_rectangle((rectangle_t){0, 0, 50, 50}, 3);


    
    /* Working :
    while (1){
        keyboard_state_t keys = keyboard_scan();
        screen_clear();
        if (keyboard_key_down(keys, KEY_QWERTY_ENTER) || keyboard_key_down(keys, KEY_AZERTY_ENTER)) {
            screen_print((point_t){0, 0}, "Enter pressed", true, 15);
        } else {
            screen_print((point_t){0, 0}, "Press Enter", true, 15);
        }
        sleep(200);
        
    }
    */

    /*
    screen_draw_rectangle((rectangle_t){0, 0, char_width, char_height}, 3);
    screen_print((point_t){1, 0}, "A", true, 15);
    screen_draw_rectangle((rectangle_t){char_width, char_height, char_width, char_height}, 3);
    screen_print((point_t){0, 1}, "A", true, 15);
    */

    
    char* buffer[256];
    *buffer = screen_print_input_string((point_t){0, 0}, true, 15);

    screen_clear();
    screen_print((point_t){0, 0}, "You entered:", true, 15);
    screen_print((point_t){0, 1}, *buffer, true, 15);

    while (1){

    }

}



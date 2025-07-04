#include "kernel.h"

#define VIDEO_MEMORY ((uint8_t*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200


void _start() {
    screen_change_font(font8x8, 8, 8);
    /*
    screen_print((point_t){0, 0}, "0123456789\nabcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n.,:;!?@#$%^&*()[]{}<>/\\|-_+=\'\"`~ ");
    screen_change_font(font6x6, 6, 6);
    screen_print((point_t){0, 10}, "0123456789\nabcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n.,:;!?@#$%^&*()[]{}<>/\\|-_+=\'\"`~ ");
    */

    const char* ascii_art[] = {
        "  ___                         ___   ____  ",
        " / _ \\ _   _ _ __ __ _ _ __  / _ \\ / ___| ",
        "| | | | | | | '__/ _` | '_ \\| | | \\___ \\ ",
        "| |_| | |_| | | | (_| | | | | |_| |___) |",
        " \\___/ \\__,_|_|  \\__,_|_| |_|\\___/|____/ "
    };

    screen_ascii_art((point_t){0, 0}, ascii_art, sizeof(ascii_art) / sizeof(ascii_art[0]));

    //------------------------------------------------------------------

    screen_draw_rectangle((rectangle_t){0, 70, 50, 50}, 15); // White
    screen_draw_rectangle_outline((rectangle_t){100, 70, 50, 50}, 4); // Red

    screen_print((point_t){0, 20}, "Hello");
    screen_print_dec((point_t){10, 20}, 12345);
    screen_print_hex((point_t){20, 20}, 0x1234AB);



    while (1) {}
}

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

    while (1) {}
}

#include "kernel.h"

void _start() {
    screen_clear();
    idt_init();

    const char* ascii_art[] = {
        "  ___                         ___   ____  ",
        " / _ \\ _   _ _ __ __ _ _ __  / _ \\ / ___| ",
        "| | | | | | | '__/ _` | '_ \\| | | \\___ \\ ",
        "| |_| | |_| | | | (_| | | | | |_| |___) |",
        " \\___/ \\__,_|_|  \\__,_|_| |_|\\___/|____/ "
    };

    screen_ascii_art((point_t){0, 0}, ascii_art, 5);

    screen_print((point_t){0,7}, "Welcome to OuranOS!");

    screen_draw_rectangle_outline((rectangle_t){50, 10, 20, 10}, 0x4F);

    screen_draw_rectangle((rectangle_t){51, 11, 20, 10}, 0x1F);

    while (1) {}
}
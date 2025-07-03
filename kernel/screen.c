#include "screen.h"

void screen_clear() {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i] = 0x0700 | ' '; 
    }
}

void screen_print(point_t point, const char *str) {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;
    int offset = point.y * 80 + point.x;
    for (int i = 0; str[i] != '\0' && (offset + i) < 80 * 25; i++) {
        video[offset + i] = 0x0700 | str[i];
    }
}

void screen_print_dec(point_t p, int value) {
    char buffer[16];
    itoa(value, buffer, 10);
    screen_print(p, buffer);
}

void screen_print_hex(point_t p, unsigned int value) {
    char buffer[16];
    itoa(value, buffer, 16);
    screen_print(p, "0x");
    screen_print((point_t){p.x + 2, p.y}, buffer); 
}

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

void screen_draw_pixel(point_t p, unsigned char color) {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;
    if (p.x >= 0 && p.x < 80 && p.y >= 0 && p.y < 25) {
        int offset = p.y * 80 + p.x;
        video[offset] = (color << 8) | ' '; // Set the color and character
    }
}

void screen_draw_rectangle(rectangle_t rect, unsigned char color) {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;
    for (int y = 0; y < rect.height; y++) {
        for (int x = 0; x < rect.width; x++) {
            int offset = (rect.y + y) * 80 + (rect.x + x);
            if (offset < 80 * 25) {
                video[offset] = (color << 8) | ' ';
            }
        }
    }
}

void screen_draw_rectangle_outline(rectangle_t rect, unsigned char color) {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;

    for (int x = 0; x < rect.width; x++) {
        if ((rect.x + x) < 80) {
            video[(rect.y * 80) + (rect.x + x)] = (color << 8) | ' '; // Top edge
            video[((rect.y + rect.height - 1) * 80) + (rect.x + x)] = (color << 8) | ' '; // Bottom edge
        }
    }

    for (int y = 0; y < rect.height; y++) {
        if ((rect.y + y) < 25) {
            video[((rect.y + y) * 80) + rect.x] = (color << 8) | ' '; // Left edge
            video[((rect.y + y) * 80) + (rect.x + rect.width - 1)] = (color << 8) | ' '; // Right edge
        }
    }
}

void screen_ascii_art(point_t p, const char **art, int lines) {
    for (int i = 0; i < lines; i++) {
        screen_print((point_t){p.x, p.y + i}, art[i]);
    }
}

void screen_set_cursor(uint16_t pos) {
    // Envoyer les 8 bits de poids fort (high byte)
    outb(0x3D4, 0x0E);
    outb(0x3D5, (pos >> 8) & 0xFF);

    // Envoyer les 8 bits de poids faible (low byte)
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
}

static int cursor_pos = 1;

void screen_put_char(point_t p,     char c) {
    volatile unsigned short *video = (volatile unsigned short*)0xB8000;
    if (c == '\n') {
        cursor_pos += 80 - (cursor_pos % 80);
    } else if (c == '\b') {
        if (cursor_pos > 0) cursor_pos--;
        video[cursor_pos] = 0x0700 | ' ';
    } else {
        video[cursor_pos++] = 0x0700 | c;
    }
    screen_set_cursor(cursor_pos);
}

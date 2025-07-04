#include "kernel.h"

#define VIDEO_MEMORY ((volatile unsigned char*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

void screen_clear() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VIDEO_MEMORY[i] = 0;
    }
}

void screen_draw_char(int x, int y, char c, unsigned char color) {
    const unsigned char *glyph = current_font[(unsigned char)c];
    for (int row = 0; row < char_height; row++) {
        unsigned char bits = glyph[row];
        for (int col = 0; col < char_width; col++) {
            if (bits & (1 << (7 - col))) {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                    VIDEO_MEMORY[py * SCREEN_WIDTH + px] = color;
                }
            }
        }
    }
}

void screen_print(point_t point, const char *str) {
    int cursor_x = point.x * char_width;
    int cursor_y = point.y * char_height;
    while (*str) {
        if (*str == '\n') {
            cursor_x = point.x * char_width;
            cursor_y += char_height;
        } else {
            screen_draw_char(cursor_x, cursor_y, *str, 15); 
            cursor_x += char_width;
        }
        str++;
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
    if (p.x >= 0 && p.x < SCREEN_WIDTH && p.y >= 0 && p.y < SCREEN_HEIGHT) {
        VIDEO_MEMORY[p.y * SCREEN_WIDTH + p.x] = color;
    }
}

void screen_draw_rectangle(rectangle_t rect, unsigned char color) {
    for (int y = 0; y < rect.height; y++) {
        for (int x = 0; x < rect.width; x++) {
            int px = rect.x + x;
            int py = rect.y + y;
            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                VIDEO_MEMORY[py * SCREEN_WIDTH + px] = color;
            }
        }
    }
}

void screen_draw_rectangle_outline(rectangle_t rect, unsigned char color) {
    for (int x = 0; x < rect.width; x++) {
        int px = rect.x + x;
        if (px >= 0 && px < SCREEN_WIDTH) {
            if (rect.y >= 0 && rect.y < SCREEN_HEIGHT)
                VIDEO_MEMORY[rect.y * SCREEN_WIDTH + px] = color;
            if ((rect.y + rect.height - 1) >= 0 && (rect.y + rect.height - 1) < SCREEN_HEIGHT)
                VIDEO_MEMORY[(rect.y + rect.height - 1) * SCREEN_WIDTH + px] = color;
        }
    }

    for (int y = 0; y < rect.height; y++) {
        int py = rect.y + y;
        if (py >= 0 && py < SCREEN_HEIGHT) {
            if (rect.x >= 0 && rect.x < SCREEN_WIDTH)
                VIDEO_MEMORY[py * SCREEN_WIDTH + rect.x] = color;
            if ((rect.x + rect.width - 1) >= 0 && (rect.x + rect.width - 1) < SCREEN_WIDTH)
                VIDEO_MEMORY[py * SCREEN_WIDTH + (rect.x + rect.width - 1)] = color;
        }
    }
}

void screen_ascii_art(point_t p, const char **art, int lines) {
    for (int i = 0; i < lines; i++) {
        screen_print((point_t){p.x, p.y + i}, art[i]);
    }
}

// Cursor doesn't exist in 13h - placeholder
void screen_set_cursor(uint16_t pos) {
    (void)pos;
}

// Emulate cursor
static int cursor_pos_x = 0;
static int cursor_pos_y = 0;

void screen_put_char(point_t p, char c) {
    if (c == '\n') {
        cursor_pos_x = 0;
        cursor_pos_y++;
    } else if (c == '\b') {
        if (cursor_pos_x > 0) cursor_pos_x--;
        screen_draw_char(cursor_pos_x * char_width, cursor_pos_y * char_height, ' ', 0); 
    } else {
        screen_draw_char(cursor_pos_x * char_width, cursor_pos_y * char_height, c, 15);
        cursor_pos_x++;
        if (cursor_pos_x * char_width >= SCREEN_WIDTH) {
            cursor_pos_x = 0;
            cursor_pos_y++;
        }
    }
}

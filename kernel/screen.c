#include "kernel.h"
#include "bitmap_font.h"
#include "screen.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"
#include "input.h"
#include "timer.h"
#include "string.h"
#include "debug.h"
#include "io.h"
#include "memory.h"
#include "terminal.h"

#define VIDEO_MEMORY ((volatile unsigned char*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

int background_color = 0; // black
int text_color = 15; // white

void screen_clear() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VIDEO_MEMORY[i] = background_color;
    }
}

void screen_print_char(point_t point, char c, unsigned char color) {
    const unsigned char *glyph = current_font[(unsigned char)c];
    for (int row = 0; row < char_height; row++) {
        unsigned char bits = glyph[row];
        for (int col = 0; col < char_width; col++) {
            if (bits & (1 << (7 - col))) {
                int px = point.x + col;
                int py = point.y + row;
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                    VIDEO_MEMORY[py * SCREEN_WIDTH + px] = color;
                }
            }
        }
    }
}

void screen_print(point_t point, const char *str, bool is_padding, unsigned char color) {
    int cursor_x = point.x;
    int cursor_y = point.y;
    
    if (is_padding){
        cursor_x = point.x * char_width;
        cursor_y = point.y * char_height;
    }
    
    while (*str) {
        if (*str == '\n' || cursor_x + char_width >= SCREEN_WIDTH) {
            cursor_x = point.x * char_width ;
            cursor_y += char_height + 1;
        } else {
            if (is_padding){
                screen_print_char((point_t){cursor_x, cursor_y}, *str, color); 
                cursor_x += char_width;
            }
            else {
                screen_print_char((point_t){cursor_x, cursor_y}, *str, color); 
                cursor_x += char_width;
            }
            
        }
        str++;
    }
}



void screen_print_dec(point_t p, int value, bool is_padding, unsigned char color) {
    char buffer[16];
    itoa(value, buffer, 10);
    if (is_padding) {
        screen_print(p, buffer, true, color);
    }
    else {
        screen_print(p, buffer, false, color);
    }
    
}

void screen_print_hex(point_t p, unsigned int value, bool is_padding, unsigned char color) {
    char buffer[16];
    itoa(value, buffer, 16);

    if (is_padding) {
        screen_print(p, "0x", true, color);
        screen_print((point_t){p.x + 2, p.y}, buffer, true, color); 
    }
    else {
        screen_print(p, "0x", false, color);
        screen_print((point_t){p.x + 2, p.y}, buffer, false, color); 
    }

    
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

void screen_print_ascii_art(point_t p, const char **art, int lines, bool is_padding, unsigned char color) {
    for (int i = 0; i < lines; i++) {
        if (is_padding) {
            screen_print((point_t){p.x, p.y + i}, art[i], true, color);
        } else {
            screen_print((point_t){p.x, p.y + i}, art[i], false, color);
        }
       
    }
}

#ifndef SCREEN_H
#define SCREEN_H

#include "kernel.h"

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} rectangle_t;

void screen_clear();
void screen_print(point_t point, const char *str);
void screen_print_dec(point_t p, int value);
void screen_print_hex(point_t p, unsigned int value);
void screen_draw_pixel(point_t p, unsigned char color);
void screen_draw_rectangle(rectangle_t rect, unsigned char color);
void screen_draw_rectangle_outline(rectangle_t rect, unsigned char color);
void screen_ascii_art(point_t p, const char **art, int lines);

#endif
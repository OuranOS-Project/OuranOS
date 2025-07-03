#ifndef SCREEN_H
#define SCREEN_H

#include "memory.h"
#include "string.h"
#include "debug.h"

typedef struct {
    int x;
    int y;
} point_t;

void screen_clear();
void screen_print(point_t point, const char *str);
void screen_print_dec(point_t p, int value);
void screen_print_hex(point_t p, unsigned int value);

#endif 
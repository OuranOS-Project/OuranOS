#ifndef INPUT_H
#define INPUT_H

#include "kernel.h"

char input_char();

char* screen_print_input_string(point_t point, bool is_padding, unsigned char color);

#endif
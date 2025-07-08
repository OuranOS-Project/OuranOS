#ifndef SCREEN_H
#define SCREEN_H

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

extern int background_color;
extern int text_color;

void screen_clear();

void screen_print_char(point_t point, char c, unsigned char color);

//void screen_print_char(point_t point, char c, bool is_padding, unsigned char color);

void screen_print(point_t point, const char *str, bool is_padding, unsigned char color);
void screen_print_dec(point_t p, int value, bool is_padding, unsigned char color);
void screen_print_hex(point_t p, unsigned int value, bool is_padding, unsigned char color);
void screen_print_ascii_art(point_t p, const char **art, int lines, bool is_padding, unsigned char color);

void screen_draw_pixel(point_t p, unsigned char color);
void screen_draw_rectangle(rectangle_t rect, unsigned char color);
void screen_draw_rectangle_outline(rectangle_t rect, unsigned char color);

void screen_set_cursor(uint16_t pos);

#endif
#ifndef BITMAP_FONT_H
#define BITMAP_FONT_H

extern int char_width;
extern int char_height;

extern const unsigned char (*current_font)[8];

void screen_change_font(const unsigned char font[128][8], int width, int height);

extern const unsigned char font8x8[128][8];

extern const unsigned char font6x6[128][8];

#endif
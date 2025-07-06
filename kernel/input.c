#include "kernel.h"
#include "screen.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"
#include "input.h"
#include "timer.h"
#include "bitmap_font.h"
#include "string.h"
#include "debug.h"
#include "io.h"
#include "memory.h"


typedef struct {
    uint8_t scancode;
    char normal;
    char shifted;
} keymap_entry_t;

char input_char() {
    static uint8_t prev_keys[256] = {0};
    keyboard_state_t keys = keyboard_scan();
    int shift = keyboard_key_down(keys, KEY_QWERTY_LSHIFT) || keyboard_key_down(keys, KEY_QWERTY_RSHIFT);

    static const keymap_entry_t keymap[] = {
        { KEY_QWERTY_A, 'a', 'A' }, { KEY_QWERTY_B, 'b', 'B' }, { KEY_QWERTY_C, 'c', 'C' },
        { KEY_QWERTY_D, 'd', 'D' }, { KEY_QWERTY_E, 'e', 'E' }, { KEY_QWERTY_F, 'f', 'F' },
        { KEY_QWERTY_G, 'g', 'G' }, { KEY_QWERTY_H, 'h', 'H' }, { KEY_QWERTY_I, 'i', 'I' },
        { KEY_QWERTY_J, 'j', 'J' }, { KEY_QWERTY_K, 'k', 'K' }, { KEY_QWERTY_L, 'l', 'L' },
        { KEY_QWERTY_M, 'm', 'M' }, { KEY_QWERTY_N, 'n', 'N' }, { KEY_QWERTY_O, 'o', 'O' },
        { KEY_QWERTY_P, 'p', 'P' }, { KEY_QWERTY_Q, 'q', 'Q' }, { KEY_QWERTY_R, 'r', 'R' },
        { KEY_QWERTY_S, 's', 'S' }, { KEY_QWERTY_T, 't', 'T' }, { KEY_QWERTY_U, 'u', 'U' },
        { KEY_QWERTY_V, 'v', 'V' }, { KEY_QWERTY_W, 'w', 'W' }, { KEY_QWERTY_X, 'x', 'X' },
        { KEY_QWERTY_Y, 'y', 'Y' }, { KEY_QWERTY_Z, 'z', 'Z' },
        { KEY_QWERTY_0, '0', ')' }, { KEY_QWERTY_1, '1', '!' }, { KEY_QWERTY_2, '2', '@' },
        { KEY_QWERTY_3, '3', '#' }, { KEY_QWERTY_4, '4', '$' }, { KEY_QWERTY_5, '5', '%' },
        { KEY_QWERTY_6, '6', '^' }, { KEY_QWERTY_7, '7', '&' }, { KEY_QWERTY_8, '8', '*' },
        { KEY_QWERTY_9, '9', '(' },
        { KEY_QWERTY_MINUS, '-', '_' }, { KEY_QWERTY_EQUAL, '=', '+' },
        { KEY_QWERTY_COMMA, ',', '<' }, { KEY_QWERTY_DOT, '.', '>' },
        { KEY_QWERTY_SLASH, '/', '?' }, { KEY_QWERTY_BACKSLASH, '\\', '|' },
        { KEY_QWERTY_SEMICOLON, ';', ':' }, { KEY_QWERTY_QUOTE, '\'', '"' },
        { KEY_QWERTY_BACKTICK, '`', '~' }, { KEY_QWERTY_LBRACKET, '[', '{' },
        { KEY_QWERTY_RBRACKET, ']', '}' }, { KEY_QWERTY_SPACE, ' ', ' ' },
        { KEY_QWERTY_ENTER, '\n', '\n' },
        { KEY_QWERTY_BACKSPACE, '\b', '\b' }
    };;

    for (size_t i = 0; i < sizeof(keymap) / sizeof(keymap[0]); ++i) {
        int down = keyboard_key_down(keys, keymap[i].scancode);
        if (down && !prev_keys[keymap[i].scancode]) {
            prev_keys[keymap[i].scancode] = 1;
            return shift ? keymap[i].shifted : keymap[i].normal;
        } else if (!down) {
            prev_keys[keymap[i].scancode] = 0;
        }
    }
    return 0;
}

#define MAX_INPUT_LENGTH 256


char* screen_print_input_string(point_t point, bool is_padding, unsigned char color) {
    static char buffer[MAX_INPUT_LENGTH];
    size_t len = 0;
    point_t start_point = point; 

    while (1) {
        char c = input_char();

        if (c == '\n') {
            buffer[len] = '\0';
            return buffer;
        }

        if (c == '\b') { 
            if (len > 0) {
                screen_print(point, buffer, is_padding, 0);
                len--;
                buffer[len] = '\0';
            }
        }

        if (c != 0 && c != '\b' && len < MAX_INPUT_LENGTH - 1) {
            buffer[len++] = c;
            buffer[len] = '\0';
        }

        point = start_point;
        
        screen_print(point, buffer, is_padding, color);

        sleep(1);
    }
}

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60

typedef struct {
    uint8_t keys[256]; // 1 octet par scancode (0: up, 1: down)
} keyboard_state_t;

extern volatile keyboard_state_t keyboard_state;

keyboard_state_t keyboard_scan(); // retourne une copie de l’état
int keyboard_key_down(keyboard_state_t state, uint8_t scancode);

typedef enum {
    // Letters (a-z)
    KEY_QWERTY_A = 0x1E,
    KEY_QWERTY_B = 0x30,
    KEY_QWERTY_C = 0x2E,
    KEY_QWERTY_D = 0x20,
    KEY_QWERTY_E = 0x12,
    KEY_QWERTY_F = 0x21,
    KEY_QWERTY_G = 0x22,
    KEY_QWERTY_H = 0x23,
    KEY_QWERTY_I = 0x17,
    KEY_QWERTY_J = 0x24,
    KEY_QWERTY_K = 0x25,
    KEY_QWERTY_L = 0x26,
    KEY_QWERTY_M = 0x32,
    KEY_QWERTY_N = 0x31,
    KEY_QWERTY_O = 0x18,
    KEY_QWERTY_P = 0x19,
    KEY_QWERTY_Q = 0x10,
    KEY_QWERTY_R = 0x13,
    KEY_QWERTY_S = 0x1F,
    KEY_QWERTY_T = 0x14,
    KEY_QWERTY_U = 0x16,
    KEY_QWERTY_V = 0x2F,
    KEY_QWERTY_W = 0x11,
    KEY_QWERTY_X = 0x2D,
    KEY_QWERTY_Y = 0x15,
    KEY_QWERTY_Z = 0x2C,

    // Modifiers
    KEY_QWERTY_LSHIFT = 0x2A,
    KEY_QWERTY_RSHIFT = 0x36,
    KEY_QWERTY_LCTRL  = 0x1D,
    KEY_QWERTY_RCTRL  = 0x9D, // 0x1D | 0x80
    KEY_QWERTY_LALT   = 0x38,
    KEY_QWERTY_RALT   = 0xB8, // 0x38 | 0x80
    KEY_QWERTY_ENTER  = 0x1C,
    KEY_QWERTY_BACKSPACE = 0x0E, // Backspace
    KEY_QWERTY_SPACE = 0x39, // Space


    // Numbers (0–9)
    KEY_QWERTY_0 = 0x0B,
    KEY_QWERTY_1 = 0x02,
    KEY_QWERTY_2 = 0x03,
    KEY_QWERTY_3 = 0x04,
    KEY_QWERTY_4 = 0x05,
    KEY_QWERTY_5 = 0x06,
    KEY_QWERTY_6 = 0x07,
    KEY_QWERTY_7 = 0x08,
    KEY_QWERTY_8 = 0x09,
    KEY_QWERTY_9 = 0x0A,

    

    // Punctuation and symbols
    KEY_QWERTY_DOT        = 0x34, // .
    KEY_QWERTY_COMMA      = 0x33, // ,
    KEY_QWERTY_COLON      = 0x92, // :
    KEY_QWERTY_SEMICOLON  = 0x27, // ;
    KEY_QWERTY_EXCLAM     = 0x90, // !
    KEY_QWERTY_QUESTION   = 0x91, // ?
    KEY_QWERTY_AT         = 0x93, // @
    KEY_QWERTY_HASH       = 0x94, // #
    KEY_QWERTY_DOLLAR     = 0x95, // $
    KEY_QWERTY_PERCENT    = 0x96, // %
    KEY_QWERTY_CARET      = 0x97, // ^
    KEY_QWERTY_AMPERSAND  = 0x98, // &
    KEY_QWERTY_ASTERISK   = 0x99, // *
    KEY_QWERTY_LPAREN     = 0x9A, // (
    KEY_QWERTY_RPAREN     = 0x9B, // )
    KEY_QWERTY_LBRACKET   = 0x1A, // [
    KEY_QWERTY_RBRACKET   = 0x1B, // ]
    KEY_QWERTY_LBRACE     = 0x9C, // {
    KEY_QWERTY_RBRACE     = 0x9D, // }
    KEY_QWERTY_LESS       = 0x9E, // <
    KEY_QWERTY_GREATER    = 0x9F, // >
    KEY_QWERTY_SLASH      = 0x35, // /
    KEY_QWERTY_BACKSLASH  = 0x2B, // \ /
    KEY_QWERTY_PIPE       = 0xA0, // |
    KEY_QWERTY_MINUS      = 0x0C, // -
    KEY_QWERTY_UNDERSCORE = 0xA1, // _
    KEY_QWERTY_PLUS       = 0xA2, // +
    KEY_QWERTY_EQUAL      = 0x0D, // =
    KEY_QWERTY_QUOTE      = 0x28, // '
    KEY_QWERTY_DQUOTE     = 0xA3, // "
    KEY_QWERTY_BACKTICK   = 0x29, // `
    KEY_QWERTY_TILDE      = 0xA4, // ~



    // --- Letters (a-z) ---
    KEY_AZERTY_A = 0x10, // A is at Q position on QWERTY
    KEY_AZERTY_B = 0x30,
    KEY_AZERTY_C = 0x2E,
    KEY_AZERTY_D = 0x20,
    KEY_AZERTY_E = 0x12,
    KEY_AZERTY_F = 0x21,
    KEY_AZERTY_G = 0x22,
    KEY_AZERTY_H = 0x23,
    KEY_AZERTY_I = 0x17,
    KEY_AZERTY_J = 0x24,
    KEY_AZERTY_K = 0x25,
    KEY_AZERTY_L = 0x26,
    KEY_AZERTY_M = 0x32,
    KEY_AZERTY_N = 0x31,
    KEY_AZERTY_O = 0x18,
    KEY_AZERTY_P = 0x19,
    KEY_AZERTY_Q = 0x1E,
    KEY_AZERTY_R = 0x13,
    KEY_AZERTY_S = 0x1F,
    KEY_AZERTY_T = 0x14,
    KEY_AZERTY_U = 0x16,
    KEY_AZERTY_V = 0x2F,
    KEY_AZERTY_W = 0x2C,
    KEY_AZERTY_X = 0x2D,
    KEY_AZERTY_Y = 0x15,
    KEY_AZERTY_Z = 0x11,

    // --- Numbers (top row) ---
    KEY_AZERTY_1 = 0x02, // & (Shift+1: 1)
    KEY_AZERTY_2 = 0x03, // é (Shift+2: 2)
    KEY_AZERTY_3 = 0x04, // " (Shift+3: 3)
    KEY_AZERTY_4 = 0x05, // ' (Shift+4: 4)
    KEY_AZERTY_5 = 0x06, // ( (Shift+5: 5)
    KEY_AZERTY_6 = 0x07, // - (Shift+6: 6)
    KEY_AZERTY_7 = 0x08, // è (Shift+7: 7)
    KEY_AZERTY_8 = 0x09, // _ (Shift+8: 8)
    KEY_AZERTY_9 = 0x0A, // ç (Shift+9: 9)
    KEY_AZERTY_0 = 0x0B, // à (Shift+0: 0)

    // --- Punctuation & symbols ---
    KEY_AZERTY_MINUS      = 0x0C, // ) (Shift: °)
    KEY_AZERTY_EQUAL      = 0x0D, // = (Shift: +)
    KEY_AZERTY_BACKTICK   = 0x29, // ` (Shift: £)
    KEY_AZERTY_LBRACKET   = 0x1A, // ^ (dead key)
    KEY_AZERTY_RBRACKET   = 0x1B, // $ (Shift: ¤)
    KEY_AZERTY_BACKSLASH  = 0x2B, // * (Shift: µ)
    KEY_AZERTY_SEMICOLON  = 0x27, // m key line: ç
    KEY_AZERTY_QUOTE      = 0x28, // ù (Shift: %)
    KEY_AZERTY_COMMA      = 0x33, // ,
    KEY_AZERTY_DOT        = 0x34, // .
    KEY_AZERTY_SLASH      = 0x35, // -
    KEY_AZERTY_LESS       = 0x56, // < (Shift: >)

    // --- Modifiers ---
    KEY_AZERTY_LSHIFT  = 0x2A,
    KEY_AZERTY_RSHIFT  = 0x36,
    KEY_AZERTY_LCTRL   = 0x1D,
    KEY_AZERTY_RCTRL   = 0x9D,
    KEY_AZERTY_LALT    = 0x38,
    KEY_AZERTY_RALT    = 0xB8,
    KEY_AZERTY_ENTER   = 0x1C,
    KEY_AZERTY_BACKSPACE = 0x0E,
    KEY_AZERTY_SPACE = 0x39, // Space


    // --- Others (via Shift or AltGr, no unique scancode) ---
    // These are provided via combination, not separate keys:
    // ! => Shift + 1
    // ? => Shift + ,
    // @ => AltGr + 0 (depends on layout)
    // # => AltGr + 3
    // $ => RBRACKET (with or without Shift)
    // % => Shift + ù
    // ^ => LBRACKET (dead key)
    // & => 1
    // * => BACKSLASH
    // ( => 5
    // ) => MINUS
    // [ ] { } => Usually via AltGr or remapped
    // < > => LESS key (Shifted)
    // / => SLASH
    // \ => Not present on FR AZERTY (needs AltGr or remap)
    // | => AltGr + 6 (typically)
    // _ => 8
    // + => Shift + EQUAL
    // = => EQUAL
    // ' => often via key `'` on ISO keyboards
    // " => 3
    // ` => BACKTICK
    // ~ => often AltGr + 2 or not available natively

} keycode_t;


extern void isr33(); // From keyboard_isr.s

void keyboard_init();
void keyboard_handler();

extern const char scancode_table_qwerty[128];
extern const char scancode_table_azerty[128];

#endif
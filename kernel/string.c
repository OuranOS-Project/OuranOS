#include "string.h"

int strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

char *itoa(int value, char *str, int base) {
    char *digits = "0123456789ABCDEF";
    char *ptr = str;
    char *start = str;
    unsigned int num = (unsigned int)value;
    int is_negative = 0;

    if (value == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return str;
    }

    if (value < 0 && base == 10) {
        is_negative = 1;
        num = -value;
    }

    while (num > 0) {
        *ptr++ = digits[num % base];
        num /= base;
    }

    if (is_negative) {
        *ptr++ = '-';
    }

    *ptr = '\0';

    for (char *left = start, *right = ptr - 1; left < right; left++, right--) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
    }

    return str;
}

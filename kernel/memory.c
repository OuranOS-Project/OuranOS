#include "memory.h"

void *memset(void *dst, int value, unsigned int count) {
    unsigned char *ptr = (unsigned char*)dst;
    while (count--) {
        *ptr++ = (unsigned char)value;
    }
    return dst;
}

void *memcpy(void *dst, const void *src, unsigned int count) {
    unsigned char *d = (unsigned char*)dst;
    const unsigned char *s = (const unsigned char*)src;
    while (count--) {
        *d++ = *s++;
    }
    return dst;
}

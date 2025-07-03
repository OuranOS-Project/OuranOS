#ifndef STRING_H
#define STRING_H

#include "kernel.h"

int strlen(const char *str); // Returns the length of the string
int strcmp(const char *s1, const char *s2); // Compares two strings and returns 0 if they are equal, non-zero otherwise
char *itoa(int value, char *str, int base); // Converts an integer to a string in the specified base (e.g., 10 for decimal, 16 for hexadecimal)

#endif

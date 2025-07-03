#ifndef DEBUG_H
#define DEBUG_H

#include "screen.h"
#include "memory.h"
#include "string.h"

#define assert(expr) ((expr) ? (void)0 : debug_panic("Assertion failed: " #expr))

void debug_panic(const char *msg);

#endif
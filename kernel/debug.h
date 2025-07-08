#ifndef DEBUG_H
#define DEBUG_H


#define assert(expr) ((expr) ? (void)0 : debug_panic("Assertion failed: " #expr))

void debug_panic(const char *msg);

#endif
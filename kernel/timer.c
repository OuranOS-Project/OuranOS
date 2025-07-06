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

// Not 100% accurate lol 20s sleep -> 23s


volatile uint32_t timer_ticks = 0;

// PIT ports
#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43

void timer_handler() {
    timer_ticks++;
}

void timer_init(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;
    outb(PIT_COMMAND, 0x36); // Command: channel 0, lobyte/hibyte, mode 3, binary
    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF)); // Low byte
    outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF)); // High byte
    timer_ticks = 0;
}

void sleep(uint32_t ms) {
    uint32_t start = timer_ticks;
    while ((timer_ticks - start) < ms) {
        __asm__ volatile ("hlt"); // Wait for interrupt
    }
}

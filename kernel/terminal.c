#include "kernel.h"
#include "bitmap_font.h"
#include "screen.h"
#include "idt.h"
#include "pic.h"
#include "keyboard.h"
#include "input.h"
#include "timer.h"
#include "string.h"
#include "debug.h"
#include "io.h"
#include "memory.h"
#include "terminal.h"

const char* terminal_command_names[TERMINAL_COMMAND_COUNT] = {
    "help",
    "cls",
    "echo",
    "ls",
    "cd",
    "mkdir",
    "create",
    "edit",
    "rm",
    "cp",
    "mv"
};

void terminal_command_help() {
    for (int i = 0; i < TERMINAL_COMMAND_COUNT; i++) {
        char buffer[64];
        const char *src = terminal_command_names[i];
        size_t j = 0;

        while (src[j] && j < sizeof(buffer) - 2) {  
            buffer[j] = src[j];
            j++;
        }

        buffer[j++] = '\n';
        buffer[j] = '\0';

        screen_print((point_t){0, i * 10}, buffer, true, 15);
    }
}

void terminal_command_cls() {
    screen_clear();
}

void terminal_command_echo(const char* args) {
    if (args && *args) {
        screen_print((point_t){0, 0}, args, true, 15);
    } else {
        screen_print((point_t){0, 0}, "No arguments provided.", true, 15);
    }
}


void terminal_command_ls() {
    // Placeholder
    screen_print((point_t){0, 0}, "ls", true, 15);
}

void terminal_command_cd(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "cd", true, 15);
}

void terminal_command_mkdir(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "mkdir", true, 15);
}

void terminal_command_create(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "create", true, 15);
}

void terminal_command_edit(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "edit", true, 15);
}

void terminal_command_rm(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "rm", true, 15);
}

void terminal_command_cp(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "cp", true, 15);
}

void terminal_command_mv(const char* args) {
    // Placeholder
    screen_print((point_t){0, 0}, "mv", true, 15);
}


void terminal_execute_command(const char* command, const char* args) {
    if (strcmp(command, "help") == 0) {
        terminal_command_help();
    } 
    else if (strcmp(command, "cls") == 0) {
        terminal_command_cls();
    } 
    else if (strcmp(command, "echo") == 0) {
        terminal_command_echo(args);
    } 
    else if (strcmp(command, "ls") == 0) {
        terminal_command_ls();
    } 
    else if (strcmp(command, "cd") == 0) {
        terminal_command_cd(args);
    } 
    else if (strcmp(command, "mkdir") == 0) {
        terminal_command_mkdir(args);
    } 
    else if (strcmp(command, "create") == 0) {
        terminal_command_create(args);
    } 
    else if (strcmp(command, "edit") == 0) {
        terminal_command_edit(args);
    } 
    else if (strcmp(command, "rm") == 0) {
        terminal_command_rm(args);
    }
    else if (strcmp(command, "cp") == 0) {
        terminal_command_cp(args);
    } 
    else if (strcmp(command, "mv") == 0) {
        terminal_command_mv(args);
    } 
    else {
        screen_print((point_t){0, 0}, "Unknown command", true, 15);
    }
}

void terminal_input_to_command(const char* input) {
    char command[64];
    char args[256] = "";
    
    // Split input into command and arguments
    int i = 0;
    while (input[i] && input[i] != ' ') {
        command[i] = input[i];
        i++;
    }
    command[i] = '\0';
    
    if (input[i] == ' ') {
        i++;
        int j = 0;
        while (input[i]) {
            args[j++] = input[i++];
        }
        args[j] = '\0';
    }

    
    screen_print((point_t){0, 10}, command, true, 15);
    screen_print((point_t){0, 11}, args, true, 15);

    terminal_execute_command(command, args);
}
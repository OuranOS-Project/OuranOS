#ifndef TERMINAL_H
#define TERMINAL_H

#define TERMINAL_COMMAND_COUNT 11
extern const char* terminal_command_names[TERMINAL_COMMAND_COUNT];

void terminal_command_help();
void terminal_command_cls();
void terminal_command_echo(const char* args);
void terminal_command_ls();
void terminal_command_cd(const char* args);
void terminal_command_mkdir(const char* args);
void terminal_command_create(const char* args);
void terminal_command_edit(const char* args);
void terminal_command_rm(const char* args);
void terminal_command_cp(const char* args);
void terminal_command_mv(const char* args);
void terminal_command_cp(const char* args);
void terminal_command_mv(const char* args);
void terminal_execute_command(const char* command, const char* args);
void terminal_input_to_command(const char* input);

#endif
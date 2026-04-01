#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

#define CMD_NOT_HANDLED -1
#define MAX_TOKENS 64

int run_shell(void);

int tokenize_input(char *line, char *commande[], size_t max_tokens);
int is_exit_command(char *commande[]);

int execute_simple(char *commande[]);
int execute_command(char *commande[]);

int run_cat(char *commande[]);
int run_ls(char *commande[]);
int run_pwd(char *commande[]);
int run_cd(char *commande[]);
int run_ping(char *commande[]);
int run_echo(char *commande[]);
int run_clear(char *commande[]);
int run_true(char *commande[]);
int run_false(char *commande[]);
int run_mkdir(char *commande[]);
int run_touch(char *commande[]);
int run_help(char *commande[]);
int run_cp(char *commande[]);

#endif

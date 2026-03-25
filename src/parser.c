#include <string.h>

#include "shell.h"

int tokenize_input(char *line, char *commande[], size_t max_tokens)
{
    size_t i = 0;
    char *token = strtok(line, " ");

    while (token != NULL && i + 1 < max_tokens) {
        commande[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    commande[i] = NULL;
    return (int)i;
}

int is_exit_command(char *commande[])
{
    return commande[0] != NULL && strcmp(commande[0], "exit") == 0;
}

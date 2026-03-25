#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

int run_clear(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "clear") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] != NULL) {
        fprintf(stderr, "clear: trop d'arguments\n");
        return 1;
    }

    const char *clear_seq = "\033[2J\033[H\033[3J";
    write(STDOUT_FILENO, clear_seq, strlen(clear_seq));
    fflush(stdout);

    return 0;
}

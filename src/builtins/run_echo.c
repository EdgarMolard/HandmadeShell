#include <stdio.h>
#include <string.h>

#include "shell.h"

int run_echo(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "echo") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL) {
        printf("\n");
        return 0;
    }

    int i = 1;
    while (commande[i] != NULL) {
        printf("%s", commande[i]);
        printf(" ");
        i++;
    }

    printf("\n");
    return 0;
}

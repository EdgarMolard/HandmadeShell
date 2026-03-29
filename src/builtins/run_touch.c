#include <stdio.h>
#include <string.h>
#include "shell.h"

int run_touch(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "touch") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL) {
        fprintf(stderr, "touch: argument manquant\n");
        return 1;
    }

    if (commande[2] != NULL) {
        fprintf(stderr, "touch: trop d'arguments\n");
        return 1;
    }

    FILE *file = fopen(commande[1], "a");
    if (file == NULL) {
        perror("touch");
        return 1;
    }

    fclose(file);
    return 0;
}
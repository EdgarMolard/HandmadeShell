#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

int run_cd(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "cd") != 0) {
        return CMD_NOT_HANDLED;
    }

    char *target = commande[1];
    if (target == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            fprintf(stderr, "cd: HOME non defini\n");
            return 1;
        }
    }

    if (commande[2] != NULL) {
        fprintf(stderr, "cd: trop d'arguments\n");
        return 1;
    }

    if (chdir(target) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

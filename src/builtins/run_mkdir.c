#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"

int run_mkdir(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "mkdir") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL) {
        fprintf(stderr, "mkdir: argument manquant\n");
        return 1;
    }

    if (commande[2] != NULL) {
        fprintf(stderr, "mkdir: trop d'arguments\n");
        return 1;
    }

    if (mkdir(commande[1], 0755) != 0) {
        perror("mkdir");
        return 1;
    }

    return 0;

}
#include <stdio.h>
#include <string.h>

#include "shell.h"

int run_cat(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "cat") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL) {
        fprintf(stderr, "cat: Pas assez d'arguments\n");
        return 1;
    }

    if (commande[2] != NULL) {
        fprintf(stderr, "cat: Trop d'argument, ce cat ne lit qu'un seul fichier par execution pour l'instant.\n");
        return 1;
    }

    FILE *f = fopen(commande[1], "r");
    if (f == NULL) {
        perror("cat");
        return 1;
    }

    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        fwrite(buf, 1, n, stdout);
    }

    fputc('\n', stdout);
    fclose(f);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "shell.h"

int run_cp(char *commande[]){


    if (commande[0] == NULL || strcmp(commande[0], "cp") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL) {
        fprintf(stderr, "cp: argument manquant: pas de fichier à copier\n");
        return 1;
    }

    if (commande[2] == NULL) {
        fprintf(stderr, "cp: argument manquant: pas de destination de copie\n");
        return 1;
    }

    if (commande[3] != NULL) {
        fprintf(stderr, "cp: trop d'arguments\n");
        return 1;
    }

    
    return 0;
}
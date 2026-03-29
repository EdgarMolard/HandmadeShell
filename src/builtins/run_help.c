#include <stdio.h>
#include <string.h>
#include "shell.h"

int run_help(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "help") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] != NULL) {
        fprintf(stderr, "help: trop d'arguments\n");
        return 1;
    }

    printf("Commandes disponibles :\n");
    printf("  ping <adresse> : Affiche 'Pong!' si l'adresse est 'localhost', sinon affiche 'Ping à <adresse>'\n");
    printf("  cat <fichier> : Affiche le contenu du fichier\n");
    printf("  echo <texte> : Affiche le texte\n");
    printf("  cd <dossier> : Change le dossier courant\n");
    printf("  pwd : Affiche le dossier courant\n");
    printf("  ls : Liste les fichiers du dossier courant\n");
    printf("  clear : Efface l'écran\n");
    printf("  true : Commande qui réussit toujours\n");
    printf("  false : Commande qui échoue toujours\n");
    printf("  mkdir <dossier> : Crée un nouveau dossier\n");
    printf("  touch <fichier> : Crée un nouveau fichier ou met à jour la date de modification d'un fichier existant\n");
    printf("  help : Affiche ce message d'aide\n");
    printf("  exit : Quitte le shell\n");

    return 0;
}
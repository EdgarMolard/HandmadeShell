#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"

int run_ping(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "ping") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] == NULL || strcmp(commande[1], "localhost") != 0) {
        printf("Veuillez preciser un parametre valide:\n\n - localhost\n - a venir ...\n");
        return 1;
    }

    int pid = fork();
    if (pid == 0) {
        char *argv[] = {"ping", "-c", "4", "google.com", NULL};
        execvp("ping", argv);
        perror("execvp");
        exit(1);
    }

    if (pid > 0) {
        int status = 0;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        return 1;
    }

    perror("fork");
    return 1;
}

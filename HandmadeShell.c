// Handmade Shell - A simple shell implementation in C
// Built along build_your_own_shell tutorial
// Compiling: gcc HandmadeShell.c -o handmade_shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_ping(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "ping") != 0) {
        return 0;
    }

    if (commande[1] == NULL || strcmp(commande[1], "localhost") != 0) {
        printf("Veuillez préciser un paramètre valide:\n\n - localhost\n - a venir ...\n");
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
        waitpid(pid, NULL, 0);
        return 1;
    }

    perror("fork");
    return 1;
}

int main(){
    printf("Welcome to Handmade Shell!\n");
    
    int on = 1;
    while(on){

        printf("eoka : "); fflush(stdout);//Affichage nom du shell avant l'entrée de commande.

        char *line = NULL;
        size_t size = 0;
        ssize_t len = getline(&line, &size, stdin);//On récupère la ligne de commande avec un string, sa taille pour la mémoire
        if (len == -1) {
            printf("\nAu revoir :p \n");
            free(line);
            exit(0);
        }
        
        if (len > 0 && line[len - 1] == '\n') {//On nettoit l'input qui garde \n en fin de ligne
            line[len - 1] = '\0';
        }

        char *commande[64];
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < 63) {
            commande[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        commande[i] = NULL;
        
        if(commande[0] != NULL && strcmp(commande[0], "exit")==0){//Si l'input dans la ligne de commande c'est un exit,
            printf("\nAu revoir :p \n");
            free(line);//On libère line et
            exit(0);//On ferme le programme
        }
        
        if (run_ping(commande)) {
            free(line);
        }
        else if (commande[0] == NULL) {
            free(line);
        }
        else//commande inconnue
        {
            printf("Commande inconnue \n");
            free(line);
        }

    }
    return 0;
}
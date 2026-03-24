// Handmade Shell - A simple shell implementation in C
// Built along build_your_own_shell tutorial
// Compiling: gcc HandmadeShell.c -o handmade_shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    printf("Welcome to Handmade Shell!\n");
    
    int on = 1;
    while(on){

        printf("eoka : "); fflush(stdout);//Affichage nom du shell avant l'entrée de commande.

        char *line = NULL;
        size_t size = 0;
        size_t len = getline(&line, &size, stdin);//On récupère la ligne de commande avec un string, sa taille pour la mémoire
        
        if (len > 0 && line[len - 1] == '\n') {//On nettoit l'input qui garde \n en fin de ligne
            line[len - 1] = '\0';
        }

        char *commande[] = {};
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            commande[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        
        if(len == -1 || strcmp(commande[0], "exit")==0){//Si l'input dans la ligne de commande c'est un exit,
            printf("\nAu revoir :p \n");
            free(line);//On libère line et
            exit(0);//On ferme le programme
        }
        
        if  (commande[1] != NULL && strcmp(commande[0], "ping")== 0 && strcmp(commande[1], "localhost")== 0){

            int pid = fork();

            if (pid == 0)
            {
                char* argv[] = {"ping", "-c", "4" ,"google.com",NULL};
                execvp("ping", argv);
                perror("execvp");
                free(line);
                exit(1);
            }
            else if (pid > 0)
            {
                waitpid(pid,NULL,0);
                free(line);
            }
            else 
            {
                perror("fork");
                free(line);
            }
        }
        else if (strcmp(commande[0], "ping")== 0 && (commande[1] != NULL && strcmp(commande[1], "localhost") > 0 ) || (strcmp(commande[0], "ping")== 0 && commande[1] == NULL))
        {
            printf("Veuillez préciser un paramètre valide :\n\n - localhost \n - à venir ...\n");
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
// Handmade Shell - A simple shell implementation in C
// Built along build_your_own_shell tutorial
// Compiling: gcc HandmadeShell.c -o handmade_shell

#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Welcome to Handmade Shell!\n");
    
    int on = 1;
    while(on){

        printf("eoka "); fflush(stdout);//Affichage nom du shell avant l'entrée de commande.

        char *line = NULL;
        size_t size = 0;
        size_t len = getline(&line, &size, stdin);//On récupère la ligne de commande avec un string, sa taille pour la mémoire
        if(len == -1){//Si l'input dans la ligne de commande c'est un exit,
            printf("Au revoir :p \n");
            free(line);//On libère line et
            exit(0);//On ferme le programme
        }
        
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }   
    }
    return 0;
}
// Handmade Shell - A simple shell implementation in C
// Built along build_your_own_shell tutorial
// Compiling: gcc HandmadeShell.c -o handmade_shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <linux/limits.h>
#include <errno.h>
#include <dirent.h>


int run_cat(char *commande[]){

    if (commande[0] == NULL || strcmp(commande[0], "cat") != 0) {
        return 0; // pas cette commande
    }

    if (commande[1] == NULL) {
        fprintf(stderr, "cat: Pas assez d'arguments\n");
        return 1;
    }else if(commande[2] == NULL)
    {
        FILE *f = fopen(commande[1],"r");
        if (f == NULL)
        {
            perror("cat");
        }else{
            char buf[4096];
            size_t n;

            while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
                fwrite(buf, 1, n, stdout);//Le cat lit le binaire d'un fichier et le copie dans le flux out
            }
            fputc('\n',stdout);
            fclose(f);
        }
    }else{
        fprintf(stderr, "cat: Trop d'argument, ce cat ne lit qu'un seul fichier par execution pour l'instant.\n");
    }
    
    return 1;
}

int run_ls(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "ls") != 0) {
        return 0; // pas cette commande
    }

    if (commande[1] != NULL && commande[2] != NULL) {
        fprintf(stderr, "ls: trop d'arguments\n");
        return 1;
    }

    // Sans argument, on liste le dossier courant.
    const char *target = ".";
    if (commande[1] != NULL) {
        target = commande[1];
    }

    // Ouvre le dossier cible et renvoie un handle DIR*.
    DIR *dir = opendir(target);
    if (dir == NULL) {
        perror("ls");
        return 1;
    }

    struct dirent *entry;
    // Compteur pour forcer des retours à la ligne réguliers.
    int items_in_line = 0;
    // Nombre de colonnes affichées par ligne.
    const int columns = 4;
    // Largeur fixe de chaque "case" d'affichage.
    const int col_width = 24;

    // errno permet de distinguer fin normale et erreur de readdir.
    errno = 0;
    while ((entry = readdir(dir)) != NULL) {
        // On masque "." et ".." pour un affichage plus propre.
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // %-*s: aligne le nom à gauche avec une largeur col_width.
        printf("%-*s", col_width, entry->d_name);
        items_in_line++;
        if (items_in_line == columns) {
            printf("\n");
            items_in_line = 0;
        }
    }

    if (errno != 0) {
        perror("ls");
    }

    if (closedir(dir) != 0) {
        perror("ls");
    }

    // Si la dernière ligne n'est pas complète, on termine proprement avec un \n.
    if (items_in_line != 0) {
        printf("\n");
    }

    return 1;
}

int run_pwd(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "pwd") != 0) {
        return 0; // pas cette commande
    }

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("pwd");
        return 1;
    }

    printf("%s\n", cwd);
    return 1; // commande traitée
}

int run_cd(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "cd") != 0) {
        return 0; // pas cette commande
    }
    char *target = commande[1];

    if (target == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            fprintf(stderr, "cd: HOME non défini\n");
            return 1;
        }
    }
    if (commande[2] != NULL) {
        fprintf(stderr, "cd: trop d'arguments\n");
        return 1;
    }

    if (chdir(target) != 0) {
        perror("cd");
    }

    return 1; // toujours traité comme builtin
}

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

int run_echo(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "echo") != 0) {
        return 0;
    }

    if (commande[1] == NULL) {
        return 1;
    }

    int i = 1;
    while (commande[i] != NULL)
    {
        printf(commande[i],"");
        printf(" ");
        i++;
    }
    printf("\n");
    return 1;
    
    
}

int run_clear(char *commande[]){

    if (commande[0] == NULL || strcmp(commande[0], "clear") != 0) {
        return 0;
    }

    if (commande[1] != NULL){
        fprintf(stderr,"clear: trop d'arguments\n");
        return 1;
    }

    const char *clear_seq = "\033[2J\033[H\033[3J";
    write(STDOUT_FILENO, clear_seq, strlen(clear_seq));
    fflush(stdout);

    return 1;
}

int main(){
    printf("Welcome to Handmade Shell!\n");
    
    int on = 1;
    while(on){


        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("pwd");
            return 1;
        }
        printf(cwd,"");
        printf("~ eoka: "); fflush(stdout);//Affichage nom du shell avant l'entrée de commande.

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

        char *commande[64] = {0};
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
        
        if (run_ping(commande) || run_cat(commande) || run_echo(commande) || run_cd(commande) || run_pwd(commande) || run_ls(commande) || run_clear(commande)){
            free(line);
        }
        else//commande inconnue
        {
            if (commande[0]==NULL){
                free(line);

            }else{
            printf("Commande inconnue \n");
            free(line);
            }
        }


    }
    return 0;
}
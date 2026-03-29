#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

int run_ls(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "ls") != 0) {
        return CMD_NOT_HANDLED;
    }

    if (commande[1] != NULL && commande[2] != NULL) {
        fprintf(stderr, "ls: trop d'arguments\n");
        return 1;
    }

    const char *target = ".";
    if (commande[1] != NULL) {
        target = commande[1];
    }

    DIR *dir = opendir(target);
    if (dir == NULL) {
        perror("ls");
        return 1;
    }

    struct dirent *entry;
    int had_error = 0;
    int items_in_line = 0;
    const int columns = 4;
    const int col_width = 24;

    errno = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("%-*s", col_width, entry->d_name);
        items_in_line++;
        if (items_in_line == columns) {
            printf("\n");
            items_in_line = 0;
        }
    }

    if (errno != 0) {
        perror("ls");
        had_error = 1;
    }

    if (closedir(dir) != 0) {
        perror("ls");
        had_error = 1;
    }

    if (items_in_line != 0) {
        printf("\n");
    }

    return had_error ? 1 : 0;
}

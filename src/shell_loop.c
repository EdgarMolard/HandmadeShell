#define _GNU_SOURCE

#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

int run_shell(void)
{
    printf("Welcome to Handmade Shell!\n");

    while (1) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("pwd");
            return 1;
        }

        printf("%s", cwd);
        printf("~ eoka: ");
        fflush(stdout);

        char *line = NULL;
        size_t size = 0;
        ssize_t len = getline(&line, &size, stdin);
        if (len == -1) {
            printf("\nAu revoir :p \n");
            free(line);
            return 0;
        }

        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char *commande[MAX_TOKENS] = {0};
        tokenize_input(line, commande, MAX_TOKENS);

        if (is_exit_command(commande)) {
            printf("\nAu revoir :p \n");
            free(line);
            return 0;
        }

        (void)execute_command(commande);
        free(line);
    }
}

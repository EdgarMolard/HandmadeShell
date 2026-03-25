#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

int run_pwd(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "pwd") != 0) {
        return CMD_NOT_HANDLED;
    }

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("pwd");
        return 1;
    }

    printf("%s\n", cwd);
    return 0;
}

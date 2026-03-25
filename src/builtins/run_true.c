#include <string.h>

#include "shell.h"

int run_true(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "true") != 0) {
        return CMD_NOT_HANDLED;
    }

    return 0;
}

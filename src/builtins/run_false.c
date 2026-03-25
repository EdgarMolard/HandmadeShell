#include <string.h>

#include "shell.h"

int run_false(char *commande[])
{
    if (commande[0] == NULL || strcmp(commande[0], "false") != 0) {
        return CMD_NOT_HANDLED;
    }

    return 1;
}

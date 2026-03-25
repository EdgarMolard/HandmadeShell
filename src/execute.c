#include <stdio.h>
#include <string.h>

#include "shell.h"

int execute_simple(char *commande[])
{
    int status;

    if (commande[0] == NULL) {
        return 0;
    }

    status = run_ping(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_cat(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_echo(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_cd(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_pwd(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_ls(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_clear(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_true(commande);
    if (status != CMD_NOT_HANDLED) return status;

    status = run_false(commande);
    if (status != CMD_NOT_HANDLED) return status;

    if (is_exit_command(commande)) {
        return 0;
    }

    fprintf(stderr, "Commande inconnue\n");
    return 127;
}

int execute_command(char *commande[])
{
    int op_index = -1;
    int is_and = 0;
    int is_or = 0;

    for (int i = 0; commande[i] != NULL; i++) {
        if (strcmp(commande[i], "&&") == 0) {
            op_index = i;
            is_and = 1;
            break;
        }
        if (strcmp(commande[i], "||") == 0) {
            op_index = i;
            is_or = 1;
            break;
        }
    }

    if (op_index == -1) {
        return execute_simple(commande);
    }

    if (op_index == 0 || commande[op_index + 1] == NULL) {
        fprintf(stderr, "Erreur de syntaxe pres de '%s'\n", commande[op_index]);
        return 2;
    }

    char *right[MAX_TOKENS] = {0};
    int j = 0;
    for (int i = op_index + 1; commande[i] != NULL && j < MAX_TOKENS - 1; i++, j++) {
        right[j] = commande[i];
    }
    right[j] = NULL;

    commande[op_index] = NULL;

    int left_status = execute_command(commande);
    if ((is_and && left_status == 0) || (is_or && left_status != 0)) {
        return execute_command(right);
    }

    return left_status;
}

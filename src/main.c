#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/tokenize.h"

int main(void)
{
    char *line = NULL;
    t_token *token;

    while (1)
    {
        line = readline("$minishell ");
        if (line == NULL || strlen(line) == 0)
        {
            free(line);
            break;
        }
        token = tokenization(line);
        printf("line is %s\n", line);
        printf("%d\n", add_history(line));
        free(line);
    }
    printf("exit\n");
    return (0);
}

#include "invoke_commands.h"

//static void    parse(t_token tokens)
//{
//
//}

void    invoke_commands(t_token *tokens)
{
    char **argv;
    //parse(tokens);
    argv = (char **)malloc(sizeof(char*) * 3);
    argv[0] = ft_strdup(tokens->data);
    execve(tokens->data, argv, NULL);
    //while (tokens)
    //{
    //    printf("%s\n", tokens->data);
    //    tokens = tokens->next;
    //}
}

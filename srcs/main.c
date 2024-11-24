/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmogami <kmogami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:45:10 by kmogami           #+#    #+#             */
/*   Updated: 2024/11/16 20:45:11 by kmogami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tokenize.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

int main(void)
{
    char *line = NULL;
    t_token *tokens;

    while (1)
    {
        line = readline("$minishell ");
        if (line == NULL || ft_strlen(line) == 0)
        {
            free(line);
            break;
        }
        tokens = tokenization(line);
        //check_syntax(tokens);
        //tokens = expand_tokens(&tokens);
        while (tokens)
        {
            printf("token: %s\n", tokens->data);
            tokens = tokens->next;
        }
        //parse_pipe_line(tokens);
        //invoke_commands();
        //all_free();
        add_history(line);
        free(line);
    }
    printf("exit\n");
    return (SUCCESS);
}

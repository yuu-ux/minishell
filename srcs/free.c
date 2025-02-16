/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:14:52 by yehara            #+#    #+#             */
/*   Updated: 2025/02/16 20:43:40 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <invoke_commands.h>

void    all_free(kvs *environ, char **path_list, t_node *parsed_tokens)
{
    int i;

    (void)parsed_tokens;
    i = 0;
    if (environ)
    {
        while (environ[i].key)
        {
            free(environ[i].key);
            free(environ[i].value);
            i++;
        }
        free(environ);
    }
    i = 0;
    if (path_list)
    {
        while (path_list[i])
            free(path_list[i++]);
        free(path_list);
    }
    // while (parsed_tokens)
    // {
    //     i = 0;
    //     if (parsed_tokens->argv)
    //     {
    //         while (parsed_tokens->argv[i])
    //             free(parsed_tokens->argv[i]);
    //         free(parsed_tokens->argv);
    //     }
    //     free(parsed_tokens);
    //     parsed_tokens = parsed_tokens->next;
    // }
}



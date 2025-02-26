/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:04:14 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 18:32:12 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenize.h>
#include <invoke_commands.h>
#include <minishell.h>
#include <builtin.h>

int ft_isspace(int c)
{
    return ('\t' == c || '\n' == c || '\v' == c
            || '\f' == c || '\r' == c || ' ' == c);
}

int is_operators(int c)
{
    return ('|' == c || c == '<' || c == '>');
}

int is_quote(int c)
{
    return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

void	close_redirect_fd(int *fd)
{
	wrap_close(*fd);
	*fd = -1;
}

char	**convert_to_envp(t_kvs *environ)
{
	int	i;
	char **envp;
	char *temp;
	int environ_num;

	i = 0;
	environ_num = count_environ(environ);
	envp = (char **)ft_xmalloc(sizeof(char *) * (environ_num + 1));
	while (environ[i].key)
	{
		temp = ft_strjoin(environ[i].key, "=");
		envp[i] = ft_strjoin(temp, environ[i].value);
		free(temp);
		i++;
	}
	return (envp);
}


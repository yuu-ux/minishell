/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:57 by yehara            #+#    #+#             */
/*   Updated: 2025/01/23 20:05:00 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <invoke_commands.h>
#include <libft.h>
#include <minishell.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal_setting.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>
#include <utils.h>

static size_t	count_env(char **environ)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (environ[i])
	{
		count++;
		i++;
	}
	return (count);
}

static kvs	*create_env(char **environ)
{
	kvs		*env_list;
	char	**temp;
	int		i;
	int		j;
	size_t	count;

	count = count_env(environ);
	env_list = (kvs *)ft_xmalloc(sizeof(kvs) * (count + 1));
	i = 0;
	while (environ[i])
	{
		j = 0;
		temp = ft_split(environ[i], '=');
		env_list[i].key = ft_strdup(temp[0]);
		env_list[i].value = ft_strdup(temp[1]);
		while (temp[j])
			free(temp[j++]);
		free(temp[j]);
		free(temp);
		i++;
	}
	return (env_list);
}

int	main(void)
{
	char		*line;
	t_token		*tokens;
	extern char	**environ;
	kvs			*env_list;

	line = NULL;
	// unset で消えることもある
	// environは自動で更新されないため、更新する必要がある
	env_list = create_env(environ);
	signal_setting();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		else if (*line == '\0')
			continue ;
		tokens = tokenization(line);
		check_syntax(tokens);
		tokens = expand_tokens(&tokens, env_list);
		invoke_commands(tokens);
		add_history(line);
		free(line);
	}
	all_free(env_list, NULL, NULL);
	return (SUCCESS);
}

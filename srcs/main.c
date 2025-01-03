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

static size_t count_env(char **environ)
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
	size_t	count;

	count = count_env(environ);
	env_list = (kvs *)malloc(sizeof(kvs) * (count + 1));
	if (!env_list)
		return (NULL);
	ft_memset(env_list, 0, sizeof(kvs));
	i = 0;
	while (environ[i])
	{
		temp = ft_split(environ[i], '=');
		env_list[i].key = temp[0];
		env_list[i].value = temp[1];
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
			break;
		}
		else if (*line == '\0')
			continue;
		tokens = tokenization(line);
		check_syntax(tokens);
		tokens = expand_tokens(&tokens, env_list);
		invoke_commands(tokens);
		//all_free();
		add_history(line);
	}
	return (SUCCESS);
}

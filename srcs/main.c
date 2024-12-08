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

static kvs	*create_path(char **environ)
{
	kvs		*path_list;
	char	**temp;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (environ[i])
	{
		count++;
		i++;
	}
	path_list = (kvs *)malloc(sizeof(kvs) * (count + 1));
	if (!path_list)
		return (NULL);
	ft_memset(path_list, 0, sizeof(kvs));
	i = 0;
	while (environ[i])
	{
		temp = ft_split(environ[i], '=');
		path_list[i].key = temp[0];
		path_list[i].value = temp[1];
		free(temp);
		i++;
	}
	return (path_list);
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
	env_list = create_path(environ);
	signal_setting();
	while (1)
	{
		line = readline("minishell$ ");
		tokens = tokenization(line);
		check_syntax(tokens);
		tokens = expand_tokens(&tokens, env_list);
		invoke_commands(tokens);
		////all_free();
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (SUCCESS);
}

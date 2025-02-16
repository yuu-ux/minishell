/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:56:43 by yehara            #+#    #+#             */
/*   Updated: 2025/02/15 23:19:19 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>

bool	has_option(char *argv)
{
	int	i;

	i = 0;
	if (!(argv[i] == '-'))
		return (false);
	else
	{
		while (argv[++i])
		{
			if (!(argv[i] == 'n'))
				return (false);
		}
	}
	return (true);
}

char *join_message(char *result, char *argv)
{
	result = free_strjoin(result, ft_strdup(argv));
	result = free_strjoin(result, ft_strdup(" "));
	if (result == NULL)
		exit(EXIT_FAILURE);
	return (result);
}

char *create_message(char **argv, bool flg_option)
{
	int	i;
	char *result;

	i = 1;
	result = ft_strdup("");
	if (flg_option)
	{
		while (argv[i])
		{
			if (!(has_option(argv[i])))
				result = join_message(result, argv[i]);
			i++;
		}
	}
	else
	{
		while (argv[i])
		{
			result = join_message(result, argv[i]);
			i++;
		}
	}
	return (ft_chop(result));
}

int	built_echo(const t_node *parsed_tokens)
{
	bool	flg_option;

	// はじめのオプションのみ検証する
	flg_option = has_option(parsed_tokens->argv[1]);
	if (flg_option)
		printf("%s", create_message(parsed_tokens->argv, flg_option));
	else
		printf("%s\n", create_message(parsed_tokens->argv, flg_option));
	return (EXIT_SUCCESS);
}


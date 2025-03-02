/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:56:43 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 17:26:58 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	built_echo(const t_node *parsed_tokens)
{
	bool	flg_option;
	char *message;

	// はじめのオプションのみ検証する
	if (parsed_tokens->argv[1] == NULL)
		return (ft_printf("\n"), EXIT_SUCCESS);
	flg_option = has_option(parsed_tokens->argv[1]);
	message = create_message(parsed_tokens->argv, flg_option);
	if (flg_option)
		ft_printf("%s", message);
	else
		ft_printf("%s\n", message);
	free(message);
	return (EXIT_SUCCESS);
}


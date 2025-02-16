/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:58:41 by yehara            #+#    #+#             */
/*   Updated: 2025/02/17 00:10:04 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <invoke_commands.h>

bool	built_pwd(void)
{
	char *current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("pwd");
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", current_dir);
	return (EXIT_SUCCESS);
}

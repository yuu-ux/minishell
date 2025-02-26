/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:58:41 by yehara            #+#    #+#             */
/*   Updated: 2025/02/24 20:01:26 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <invoke_commands.h>
#include <builtin.h>

bool	built_pwd(t_context *context)
{
	char *current_dir;
	t_kvs *pwd;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		pwd = xgetenv("PWD", context);
		if (pwd == NULL)
		{
			perror("pwd");
			return (EXIT_FAILURE);
		}
		return (ft_printf("%s\n", pwd->value), EXIT_SUCCESS);
	}
	ft_printf("%s\n", current_dir);
	free(current_dir);
	return (EXIT_SUCCESS);
}


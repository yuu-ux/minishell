/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:58:41 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 21:36:30 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

bool	built_pwd(t_context *context)
{
	char	*current_dir;
	t_kvs	*pwd;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		pwd = xgetenv("PWD", context);
		if (pwd == NULL)
		{
			perror("pwd");
			return (setting_exit_status(context, EXIT_FAILURE));
		}
		return (printf("%s\n", pwd->value), EXIT_SUCCESS);
	}
	printf("%s\n", current_dir);
	free(current_dir);
	return (setting_exit_status(context, EXIT_SUCCESS));
}

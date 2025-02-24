/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:11 by yehara            #+#    #+#             */
/*   Updated: 2025/02/16 21:05:19 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

bool	built_cd(const t_node *parsed_tokens, t_context *context)
{
	char *pwd;
	char *old_pwd;

	old_pwd = getcwd(NULL, 0);
	chdir(parsed_tokens->argv[1]);
	pwd = getcwd(NULL, 0);
	if (xgetenv("PWD", context) == NULL)
	{
		xaddenv("PWD", pwd, context);
		xunsetenv("OLDPWD", context);
		xaddenv("OLDPWD", NULL, context);
	}
	else
	{
		xsetenv("OLDPWD", old_pwd, context);
		xsetenv("PWD", pwd, context);
	}
	free(old_pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}


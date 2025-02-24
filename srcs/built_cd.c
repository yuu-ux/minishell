/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:11 by yehara            #+#    #+#             */
/*   Updated: 2025/02/24 20:23:39 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <error.h>

void	setup_pwd(char **old_pwd, char **pwd, t_context *context)
{
	if (xgetenv("PWD", context) == NULL)
	{
		xaddenv("PWD", *pwd, context);
		xunsetenv("OLDPWD", context);
		xaddenv("OLDPWD", NULL, context);
	}
	else
	{
		if (xgetenv("OLDPWD", context) == NULL)
			xaddenv("OLDPWD", *old_pwd, context);
		else
			xsetenv("OLDPWD", *old_pwd, context);
		xsetenv("PWD", *pwd, context);
	}
	free(*old_pwd);
	free(*pwd);
}


int	count_argv(const t_node *parsed_tokens)
{
	int	count;

	count = 0;
	while (parsed_tokens->argv[count])
		count++;
	return (count);
}

bool	built_cd(const t_node *parsed_tokens, t_context *context)
{
	char	*current_pwd;
	char	*next_pwd;
	t_kvs	*home_path;

	if (count_argv(parsed_tokens) > 2)
	{
		ft_printf("bash: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	current_pwd = getcwd(NULL, 0);
	if (parsed_tokens->argv[1] == NULL)
	{
		home_path = xgetenv("HOME", context);
		if (home_path != NULL)
			chdir(home_path->value);
	}
	else if (access(parsed_tokens->argv[1], F_OK) == 0 && access(parsed_tokens->argv[1], X_OK) == 0)
		chdir(parsed_tokens->argv[1]);
	else
	{
		free(current_pwd);
		join_perror("bash: cd: ", parsed_tokens->argv[1]);
		return (EXIT_FAILURE);
	}
	next_pwd = getcwd(NULL, 0);
	setup_pwd(&current_pwd, &next_pwd, context);
	return (EXIT_SUCCESS);
}


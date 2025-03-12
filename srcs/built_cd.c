/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:11 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 21:38:33 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "utils.h"

static void	setup_pwd(char **old_pwd, char **pwd, t_context *context)
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

static int	count_argv(const t_node *parsed_tokens)
{
	int	count;

	count = 0;
	while (parsed_tokens->argv[count])
		count++;
	return (count);
}

static bool	cd_parent(char **current_pwd, t_context *context)
{
	size_t	len;
	char	*next_pwd;
	char	*old_pwd;

	if (*current_pwd == NULL)
		return (perror("cd_parent"), EXIT_FAILURE);
	old_pwd = ft_strdup(*current_pwd);
	len = ft_strlen(*current_pwd);
	while (len > 0)
	{
		if ((*current_pwd)[len] == '/')
		{
			(*current_pwd)[len] = '\0';
			break ;
		}
		len--;
	}
	chdir(*current_pwd);
	free(*current_pwd);
	next_pwd = getcwd(NULL, 0);
	setup_pwd(&old_pwd, &next_pwd, context);
	return (setting_exit_status(context, EXIT_SUCCESS));
}

static bool	cd_home(t_context *context, char **current_pwd)
{
	t_kvs	*home_path;
	char	*update_home_path;

	home_path = xgetenv("HOME", context);
	if (home_path != NULL)
	{
		update_home_path = ft_strdup(home_path->value);
		chdir(update_home_path);
		if (xgetenv("PWD", context))
			xsetenv("PWD", update_home_path, context);
		else
			xaddenv("PWD", update_home_path, context);
		free(update_home_path);
		context->exit_status = EXIT_SUCCESS;
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		context->exit_status = EXIT_FAILURE;
	}
	free(*current_pwd);
	return (context->exit_status);
}

bool	built_cd(const t_node *parsed_tokens, t_context *context)
{
	char	*current_pwd;
	char	*next_pwd;

	if (count_argv(parsed_tokens) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (setting_exit_status(context, EXIT_FAILURE));
	}
	current_pwd = getcwd(NULL, 0);
	if (parsed_tokens->argv[1] == NULL)
		return (cd_home(context, &current_pwd));
	else if (ft_strncmp(parsed_tokens->argv[1], "..", 3) == 0)
		return (cd_parent(&current_pwd, context));
	else if (access(parsed_tokens->argv[1], X_OK) == 0)
		chdir(parsed_tokens->argv[1]);
	else
	{
		free(current_pwd);
		join_perror("minishell: cd: ", parsed_tokens->argv[1]);
		return (setting_exit_status(context, EXIT_FAILURE));
	}
	next_pwd = getcwd(NULL, 0);
	setup_pwd(&current_pwd, &next_pwd, context);
	return (setting_exit_status(context, EXIT_SUCCESS));
}

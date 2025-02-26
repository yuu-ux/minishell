/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:04:14 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:09:36 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenize.h>
#include <invoke_commands.h>
#include <minishell.h>
#include <builtin.h>

int is_operators(int c)
{
    return ('|' == c || c == '<' || c == '>');
}

int is_quote(int c)
{
    return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

void	close_redirect_fd(int *fd)
{
	wrap_close(*fd);
	*fd = -1;
}

void	reset_fd(t_exe_info *info)
{
	dup2(info->saved_stdin, STDIN_FILENO);
	close_redirect_fd(&info->saved_stdin);
	dup2(info->saved_stdout, STDOUT_FILENO);
	close_redirect_fd(&info->saved_stdout);
}

void	init_saved_fd(t_exe_info *info)
{
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
}

char	**convert_to_envp(t_kvs *environ)
{
	int	i;
	char **envp;
	char *temp;
	int environ_num;

	i = 0;
	environ_num = count_environ(environ);
	envp = (char **)ft_xmalloc(sizeof(char *) * (environ_num + 1));
	while (environ[i].key)
	{
		temp = ft_strjoin(environ[i].key, "=");
		envp[i] = ft_strjoin(temp, environ[i].value);
		free(temp);
		i++;
	}
	return (envp);
}


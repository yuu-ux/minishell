/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:04:14 by yehara            #+#    #+#             */
/*   Updated: 2025/03/04 20:53:56 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	close_redirect_fd(int *fd)
{
	wrap_close(*fd);
	*fd = -1;
}


void	double_close_fd(int *fd1, int *fd2)
{
	close_redirect_fd(fd1);
	close_redirect_fd(fd2);
}

void	reset_fd(t_exe_info *info)
{
	dup2(info->saved_stdin, STDIN_FILENO);
	dup2(info->saved_stdout, STDOUT_FILENO);
	double_close_fd(&info->saved_stdin, &info->saved_stdout);
}

void	init_saved_fd(t_exe_info *info)
{
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
}

char	**convert_to_envp(t_kvs *environ)
{
	int		i;
	char	**envp;
	char	*temp;
	int		environ_num;

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

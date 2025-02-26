/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:58:54 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 17:58:59 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>

char	**get_path_list(char *env_path)
{
    char	**path_list;

	if (env_path == NULL)
		return (NULL);
    path_list = ft_split(env_path, ':');
    return (path_list);
}

size_t	count_pipe(t_node *parsed)
{
	size_t  count;

	count = 0;
	while (parsed)
	{
		if (parsed->kind == PIPE)
			count++;
		parsed = parsed->next;
	}
	return (count);
}

void wrap_dup2(int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
}

void wrap_close(int fd)
{
    if (fd != -1 && close(fd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int    initialize_info(t_exe_info *info, t_node *parsed_tokens)
{
    info->pipe_num = count_pipe(parsed_tokens);
    info->exec_count = 0;
    info->before_cmd_fd = INVALID_FD;
    info->pid = (pid_t *)ft_xmalloc((info->pipe_num + 1) * sizeof(pid_t));
	info->saved_stdin = INVALID_FD;
	info->saved_stdout = INVALID_FD;
    return (EXIT_SUCCESS);
}

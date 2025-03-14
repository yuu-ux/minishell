/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_commands.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:51:12 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/01 22:05:19 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVOKE_COMMANDS_H
# define INVOKE_COMMANDS_H

# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"

typedef enum e_std_fd
{
	IN = STDIN_FILENO,
	OUT = STDOUT_FILENO,
	ERR = STDERR_FILENO,
	INVALID_FD = -1,
}			t_std_fd;

/* invoke_commands.c */
void		invoke_commands(t_token *tokens, t_context *context);
t_node		*parse(t_token *tokens, t_node *prev_node);

/* invoke_utils.c */
char		**get_path_list(char *env_path);
size_t		count_pipe(t_node *parsed);
int			initialize_info(t_exe_info *info, t_node *parsed_tokens);
void		wrap_close(int fd);
void		wrap_dup2(int old_fd, int new_fd);
int			execute(t_node *parsed_tokens, char **path_list,
				t_context *context, t_exe_info *info);

/* execute.c */
int			child_process(t_node *parsed_tokens, t_exe_info *info,
				char **path_list, t_context *context);
int			parent_process(t_node *parsed_tokens, t_exe_info *info);

/* builtin.c */
int			exec_builtin(t_node *parsed_tokens, char **path_list,
				t_context *context, t_exe_info *info);

/* builtin_utils.c */
bool		is_builtin(const t_node *parsed_tokens);

/* heredoc.c */
bool		is_heredoc(char *argv);
bool		process_heredoc(t_node *parsed_tokens, char **path_list,
				t_context *context, t_exe_info *info);
char		*expand_heredoc(char **line, t_context *context);
int			here_document_rl_event_hook(void);
void		print_line(char **line, int fds[2]);
void		heredoc_print_error_message(char *delimiter);

#endif

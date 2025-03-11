/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:29:22 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/09 03:31:59 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

# define EXIT_STATUS_PERMISSION_DENIED 126
# define EXIT_STATUS_COMMAND_NOT_FOUND 127
# define EXIT_STATUS_INVALID 128
# define EXIT_STATUS_SYNTAX_ERROR 2
# define COMMAND_NOT_FOUND_NUM 18

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
}			t_token_type;

typedef struct s_token
{
	char			*data;
	struct s_token	*next;
	t_token_type	type;
}					t_token;

typedef struct s_exe_info
{
	pid_t	*pid;
	int		pipe_num;
	int		exec_count;
	int		before_cmd_fd;
	int		saved_stdin;
	int		saved_stdout;
	char 	*path;
	char	*error_message;
	char	*heredoc_delimiter;
}			t_exe_info;

typedef enum e_node_type
{
	CMD,
	PIPE,
}	t_node_type;

typedef struct s_node
{
	int				fds[2];
	t_node_type		kind; // CMD:0 PIPE:1
	char			**argv;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_kvs
{
	char	*key;
	char	*value;
}			t_kvs;

typedef struct s_context
{
	t_kvs	*environ;
	uint8_t	exit_status;
	bool	flg_heredoc_expand;
}			t_context;

t_context	init_context(char *envp[]);

#endif

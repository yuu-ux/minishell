/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:29:22 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/02 17:39:19 by hana/hmori       ###   ########.fr       */
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
# include "units/debug.h"
# include "units/error.h"
# include "units/expand.h"
# include "units/invoke_commands.h"
# include "units/redirect.h"
# include "units/utils.h"

# include "libft.h"

# define EXIT_STATUS_COMMAND_NOT_FOUND 127
# define EXIT_STATUS_INVALID 128
# define EXIT_STATUS_SYNTAX_ERROR 2

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
	t_token			*next;
	t_token_type	type;
}			t_token;

t_context	init_context(char *envp[]);

#endif

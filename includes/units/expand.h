/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:43:59 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/27 23:12:03 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <aio.h>

typedef struct s_token		t_token;
typedef struct s_context	t_context;
typedef struct s_kvs		t_kvs;

typedef struct s_expand {
	t_context *context;
	char	*token;
} t_expand;

t_token	*expand_tokens(t_token **_tokens, t_context *context);

// expand_utils
char	*search_env(const char *key, t_kvs *environ);
size_t	insert_env(char **buffer, char *token, t_context *context);
size_t	expand_variable(char **result, t_expand expand, int start, int i);
bool	is_expand(char *token, int i);
void	set_flg_heredoc_expand(t_token *token, t_context *context);

#endif

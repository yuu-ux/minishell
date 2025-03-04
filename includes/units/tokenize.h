/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:04:45 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/27 10:25:30 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''
# define SYNTAX_ERROR 1

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token			*next;
	t_token_type	type;
}	t_token;

t_token	*tokenization(const char *line);
bool	check_syntax(t_token *token, t_context *context);

// utils
int		is_operators(int c);
int		is_quote(int c);

// tokenize_utils
size_t	skip_quoted_token(char quote_char, const char **line);
size_t	skip_while(int (*is_skip)(int), const char **line);
size_t	skip_non_delimiter(const char **line);
t_token	*new_token(const char *line, t_token_type type);

#endif

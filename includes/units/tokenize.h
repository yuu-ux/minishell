/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:04:45 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/04 20:58:37 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''
# define SYNTAX_ERROR 1

/* tokenize.c */
t_token				*tokenization(const char *line);

/* check_syntax.c */
bool				check_syntax(t_token *token, t_context *context);

/* tokenize_utils.c */
size_t				skip_quoted_token(char quote_char, const char **line);
size_t				skip_while(int (*is_skip)(int), const char **line);
size_t				skip_non_delimiter(const char **line);
t_token				*new_token(const char *line, t_token_type type);

#endif

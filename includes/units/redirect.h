/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:17 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/27 10:27:01 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

typedef enum e_token_type	t_token_type;
typedef struct s_node		t_node;

// redirect_utils.c
bool			is_pipe(char *str);
bool			is_redirect(char *str);
t_token_type	get_token_type(const char *token);

// redirect.c
bool			do_redirections(t_node *parsed_tokens);

#endif

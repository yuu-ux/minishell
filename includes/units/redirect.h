/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:17 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/04 20:59:24 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

typedef enum e_token_type	t_token_type;
typedef struct s_node		t_node;

// redirect_utils.c
t_token_type				get_token_type(const char *token);
int							count_argv_cmd(char **argv);
bool						redirect_in(t_node *parsed_tokens, int i);
bool						redirect_out(t_node *parsed_tokens, int i);
bool						redirect_append(t_node *parsed_tokens, int i);

// redirect.c
bool						do_redirections(t_node *parsed_tokens);

#endif

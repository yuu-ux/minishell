/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:04:11 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 19:20:44 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_node		t_node;

const char					*get_token_type_string(t_token_type type);
void						print_token(t_token *head);
void						print_node(t_node *head);

#endif

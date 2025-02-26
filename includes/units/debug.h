/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:04:11 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 17:04:19 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "tokenize.h"
# include "invoke_commands.h"

const char	*get_token_type_string(t_token_type type);
void		print_token(t_token *head);
void		print_node(t_node *head);

#endif

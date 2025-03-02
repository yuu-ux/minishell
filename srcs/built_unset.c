/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:19:24 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 17:06:55 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	built_unset(const	t_node *parsed_tokens, t_context *context)
{
	int	i;

	i = 1;
	while (parsed_tokens->argv[i])
		xunsetenv(parsed_tokens->argv[i++], context);
	return (EXIT_SUCCESS);
}

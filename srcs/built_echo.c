/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:56:43 by yehara            #+#    #+#             */
/*   Updated: 2025/02/15 23:19:19 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>

int	built_echo(const t_node *parsed_tokens)
{
	printf("%s\n", parsed_tokens->argv[1]);
	return (EXIT_SUCCESS);
}

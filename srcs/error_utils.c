/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:47:39 by yehara            #+#    #+#             */
/*   Updated: 2025/02/24 18:52:35 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <invoke_commands.h>

void	join_perror(const char *s1, const char *s2)
{
	char *message;

	message = ft_strjoin(s1, s2);
	perror(message);
	free(message);
}

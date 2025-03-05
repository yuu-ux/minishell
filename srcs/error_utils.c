/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:47:39 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:19:26 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_perror(const char *s1, const char *s2)
{
	char	*message;

	message = ft_strjoin(s1, s2);
	perror(message);
	free(message);
}

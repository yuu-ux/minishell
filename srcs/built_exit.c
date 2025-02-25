/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:40:48 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 17:41:14 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <utils.h>

bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info)
{
    ft_printf("exit\n");
	reset_fd(info);
	free_after_invoke(path_list, parsed_tokens, info);
	free_context(context);
    exit(EXIT_SUCCESS);
}

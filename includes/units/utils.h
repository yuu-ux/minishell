/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:00:57 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/03 21:35:29 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* utils.c */
void	free_environ(t_context *context);
void	close_redirect_fd(int *fd);
char	**convert_to_envp(t_kvs *environ);
void	free_after_invoke(char **path_list, t_node *parsed_tokens, t_exe_info *info);
void	init_saved_fd(t_exe_info *info);
void	reset_fd(t_exe_info *info);
void	free_tokens(t_token **tokens);

/* environ_units.c */
int		count_environ(t_kvs *environ);
t_kvs	*xgetenv(const char *name, t_context *context);

/* status_units.c */
void	setting_status(t_context *context);
bool	setting_exit_status(t_context *context, int status);

#endif

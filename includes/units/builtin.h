/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:46:08 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/02 17:09:05 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// built_func
bool	built_echo(const t_node *parsed_tokens);
bool	built_cd(const t_node *parsed_tokens, t_context *context);
bool	built_pwd(t_context *context);
bool	built_export(const	t_node *parsed_tokens, t_context *context);
bool	built_unset(const	t_node *parsed_tokens, t_context *context);
bool	built_env(t_context *context);
bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info);

// builtin_utils.c
bool    is_builtin(const t_node *parsed_tokens);
int		xsetenv(char *name, char *value, t_context *context);
void	xaddenv(char *name, char *value, t_context *context);
void	xunsetenv(const char *name, t_context *context);

#endif

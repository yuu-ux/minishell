/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:46:08 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 19:11:38 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_node		t_node;
typedef struct s_kvs		t_kvs;
typedef struct s_exe_info	t_exe_info;
typedef struct s_context	t_context;

// built_func
bool	built_echo(const t_node *parsed_tokens, t_context *context);
bool	built_cd(const t_node *parsed_tokens, t_context *context);
bool	built_pwd(t_context *context);
bool	built_export(const	t_node *parsed_tokens, t_context *context);
bool	built_unset(const	t_node *parsed_tokens, t_context *context);
bool	built_env(t_context *context);
bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info);

// builtin_utils.c
t_kvs	*xgetenv(const char *name, t_context *context);
int		xsetenv(char *name, char *value, t_context *context);
int		count_environ(t_kvs *environ);
void	xaddenv(char *name, char *value, t_context *context);
void	xunsetenv(const char *name, t_context *context);

#endif

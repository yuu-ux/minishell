/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:00:57 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/27 10:23:54 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_context	t_context;
typedef struct s_kvs		t_kvs;
typedef struct s_node		t_node;
typedef struct s_exe_info	t_exe_info;

void	free_context(t_context *context);
void	close_redirect_fd(int *fd);
char	**convert_to_envp(t_kvs *environ);
void	free_after_invoke(char **path_list, t_node *parsed_tokens, t_exe_info *info);// line too long
void	init_saved_fd(t_exe_info *info);
void	reset_fd(t_exe_info *info);

#endif

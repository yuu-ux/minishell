/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:17:50 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/02 15:33:18 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_SETTING_H
# define SIGNAL_SETTING_H

# include <signal.h>
# include "minishell.h"

extern volatile sig_atomic_t	g_sig;

/* signal_setting.c */
void							parent_signal_setting(void);
void							parent_override_signal_setting(void);
void							child_signal_setting(void);

/* signal_handler.c */
void							signal_handler(int signum);
void							heredoc_parent_sigint_handler(int signum);
void							sigint_handler(int signum);
void							parent_override_signal_handler(int signum);
void							heredoc_child_signal_setting(void);
void							setting_status(t_context *context);

#endif

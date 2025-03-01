/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:17:50 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/27 10:19:51 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_SETTING_H
# define SIGNAL_SETTING_H

# include <signal.h>

typedef struct sigaction	t_sigaction;

void	signal_setting(void);
void	pear_signal_setting(void);

#endif

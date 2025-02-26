/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:29:22 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 17:49:07 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define FAILURE 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>

# include <readline/history.h>
# include <readline/readline.h>

# include "units/builtin.h"
# include "units/debug.h"
# include "units/error.h"
# include "units/expand.h"
# include "units/invoke_commands.h"
# include "units/redirect.h"
# include "units/signal_setting.h"
# include "units/tokenize.h"
# include "units/utils.h"

# include "libft.h"

typedef struct s_kvs
{
    char *key;
    char *value;
}	t_kvs;

t_context	*init_context(char *envp[]);

#endif

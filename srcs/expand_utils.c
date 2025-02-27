/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:19:44 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 18:19:46 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_expand(char *token, int i)
{
	return (token[i] == '$' && !(token[i + 1] == '\0' || token[i + 1] == '$'));
}

char	*search_env(const char *key, t_kvs *environ)
{
	int	i;
	char *result;

	i = 0;
	result = NULL;
	while (environ[i].key)
	{
		// null 文字まで比較させるための+1
		if (!ft_strncmp(environ[i].key, key, ft_strlen(environ[i].key) + 1))
			result = ft_strdup(environ[i].value);
		i++;
	}
	// key のみ存在する場合、value が NULL になる
	if (result == NULL)
		return (ft_strdup(""));
	return (result);
}

size_t	count_key_len(char *token)
{
	size_t	i;

	i = 0;
	while ((ft_isalnum(token[i]) || token[i] == '_')
		&& token[i])
		i++;
	return (i);
}

size_t	insert_env(char **buffer, char *token, t_context *context)
{
	size_t	key_len;
	char	*value;
    char *substr;
	int	i;

	i = 0;
	key_len = 0;
	if (token[i] == '$')
		i++;
	if (token[i - 1] == '$' && token[i] == '?')
	{
		value = ft_itoa(context->exit_status);
		key_len++;
	}
	else
	{
		key_len = count_key_len(&token[i]);
		substr = ft_substr(token, i, key_len);
		value = search_env(substr, context->environ);
		free(substr);
	}
	*buffer = free_strjoin(*buffer, value);
	return (key_len);
}


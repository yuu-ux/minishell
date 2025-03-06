/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:19:56 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 18:19:57 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invoke_commands.h"

static t_node	*new_node(char **argv)
{
	t_node	*node;

	node = (t_node *)ft_xmalloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->fds[IN] = INVALID_FD;
	node->fds[OUT] = INVALID_FD;
	node->argv = argv;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static size_t	count_word_node(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens && (tokens->type != TOKEN_PIPE))
	{
		if (tokens->data[0] || tokens->next == NULL)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	*token_set_send_free(t_token **tokens, char *(*func)(const char *))
{
	char	*result;
	t_token	*before_token;

	before_token = *tokens;
	(*tokens) = before_token->next;
	result = NULL;
	if (func)
		result = func(before_token->data);
	free(before_token->data);
	free(before_token);
	return (result);
}

static char	**create_argv(t_token **tokens)
{
	int		i;
	char	**result;
	size_t	word_num;

	word_num = count_word_node(*tokens);
	if (word_num == 0)
	{
		token_set_send_free(tokens, NULL);
		return (NULL);
	}
	result = (char **)ft_xmalloc((word_num + 1) * sizeof(char *));
	i = 0;
	while (i < (int)word_num)
	{
		if ((*tokens)->data[0] || (*tokens)->next == NULL)
			result[i++] = token_set_send_free(tokens, ft_strdup);
		else
			token_set_send_free(tokens, NULL);
	}
	return (result);
}

t_node	*parse(t_token *tokens, t_node *prev_node)
{
	t_node	*current;

	if (tokens == NULL)
		return (NULL);
	current = new_node(create_argv(&tokens));
	current->prev = NULL;
	if (prev_node)
		current->prev = prev_node;
	if (current->argv)
		current->kind = CMD;
	else
		current->kind = PIPE;
	current->next = parse(tokens, current);
	return (current);
}

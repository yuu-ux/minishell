#include <debug.h>
#include <expand.h>
#include <libft.h>
#include <tokenize.h>

static char	*search_env(const char *key, kvs *path_list)
{
	int	i;

	i = 0;
	while (path_list[i].key)
	{
		// null 文字まで比較させるための+1
		if (!ft_strncmp(path_list[i].key, key, ft_strlen(path_list[i].key) + 1))
			return (path_list[i].value);
		i++;
	}
	return (NULL);
}

static size_t	count_key_len(char *token, int t_index)
{
	size_t	i;

	i = 0;
	while ((ft_isalnum(token[t_index]) || token[t_index] == '_')
		&& token[t_index])
	{
		i++;
		t_index++;
	}
	return (i);
}

static size_t	insert_env(char **buffer, char *token, kvs *path_list)
{
	size_t	key_len;
	char	*value;

	if (token[0] == '$')
		token++;
	key_len = count_key_len(token, 0);
	value = search_env(ft_substr(token, 0, key_len), path_list);
	if (value == NULL)
		value = ft_strdup("");
	*buffer = ft_strjoin(*buffer, value);
	return (key_len);
}

static size_t	delete_single_quote(char **result, char *token)
{
	size_t	i;

	i = 0;
	i++;
	while (token[i] != SINGLE_QUOTE)
		i++;
	*result = ft_strjoin(*result, ft_substr(token, 1, i - 1));
	// 「'」の次を指すために、+1
	return (i + 1);
}

static size_t	expand_double_quote(char **result, char *token, kvs *path_list)
{
	size_t	i;
	int		start;

	i = 1;
	start = 1;
	while (token[i] != DOUBLE_QUOTE)
	{
		if (token[i] == '$')
		{
			*result = ft_strjoin(*result, ft_substr(token, start, i - start));
			// 「"」と「$」のため、i+1
			i += insert_env(result, &token[i], path_list);
			start = i + 1;
		}
		i++;
	}
	*result = ft_strjoin(*result, ft_substr(token, start, i - start));
	return (i + 1);
}

static char	*expand_token(char *token, kvs *path_list)
{
	int		i;
	char	*result;
	int		start;

	i = 0;
	start = 0;
	result = ft_strdup("");
	// 変数以外の文字をカウントする
	while (token[i])
	{
		if (token[i] == SINGLE_QUOTE)
		{
			i += delete_single_quote(&result, &token[i]);
			start = i;
		}
		else if (token[i] == DOUBLE_QUOTE)
		{
			i += expand_double_quote(&result, &token[i], path_list);
			start = i;
		}
		else
		{
			if (token[i] == '$')
			{
				result = ft_strjoin(result, ft_substr(token, start, i - start));
				i += insert_env(&result, &token[i], path_list);
				// $ 文字分+1
				start = i + 1;
			}
			i++;
		}
	}
	result = ft_strjoin(result, ft_substr(token, start, i - start));
	return (result);
}

t_token	*expand_tokens(t_token **_tokens, kvs *path_list)
{
	t_token	*head;
	t_token	*tokens;

	head = *_tokens;
	tokens = *_tokens;
	while (tokens)
	{
		tokens->data = expand_token(tokens->data, path_list);
		tokens = tokens->next;
	}
	return (head);
}

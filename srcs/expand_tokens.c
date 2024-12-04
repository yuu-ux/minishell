#include <tokenize.h>
#include <expand.h>
#include <libft.h>
#include <debug.h>

static char *search_env(const char *key, kvs *path_list)
{
	int i;

	i = 0;
	while (path_list[i].key)
	{
		// null 文字まで比較させるための+1
		if (!ft_strncmp(path_list[i].key, key, ft_strlen(path_list[i].key)+1))
			return (path_list[i].value);
		i++;
	}
	return (NULL);
}

static size_t  count_key_len(char *token, int t_index)
{
	size_t  i;

	i = 0;
	while ((ft_isalnum(token[t_index]) || token[t_index] == '_') && token[t_index])
	{
		i++;
		t_index++;
	}
	return (i);
}

static	size_t	insert_env(char **buffer, char *token, kvs *path_list)
{
	size_t key_len;
	char *value;
	size_t	value_len;

	if (token[0] == '$')
		token++;
	else
		return -1;
	key_len = count_key_len(token, 0);
	value = search_env(ft_substr(token, 0, key_len), path_list);
	if (value == NULL)
		return -1;
	value_len = ft_strlen(value);
	if (buffer)
		*buffer = ft_strjoin(*buffer, value);
	else
	{
		if (key_len < value_len)
			*buffer = (char *)ft_realloc(*buffer, value_len);
		// null 終端分の +1 文字
		ft_strlcpy(*buffer, value, value_len+1);
	}
	return (ft_strlen(value));
}


static	char *expand_token(char *token, kvs *path_list)
{
	int		i;
	int		flg;
	char	*result;
	int		res_index;
	int value_len;
	int	key_len;
	int token_len;

	i = 0;
	res_index = 0;
	flg = 0;
	token_len = ft_strlen(token);
	result = (char *)ft_calloc(token_len + 1, sizeof(char));
	while (token[i])
	{
		if (token[i] == SINGLE_QUOTE)
		{
			if (flg == 0)
				flg = 1;
			else
				flg = 0;
			i++;
		}
		else if (token[i] == '$' && flg == 0)
		{
			value_len = insert_env(&result, &token[i], path_list);
			// result のインデックスを value 文字分進める
			res_index += value_len;
			// $をスキップするため+1
			key_len = count_key_len(token, i+1);
			i += key_len+1;
			// $文字文の +1
			result = ft_realloc(result, (token_len - key_len+1) + value_len + 1);
		}
		else if (token[i] == DOUBLE_QUOTE)
			i++;
		else
		{
			result[res_index] = token[i];
			res_index++;
			i++;
		}
	}
	result[res_index] = '\0';
	return result;
}

t_token    *expand_tokens(t_token **_tokens, kvs *path_list)
{
    t_token *head;
    t_token *tokens;

    head = *_tokens;
    tokens = *_tokens;
    while (tokens)
    {
		tokens->data = expand_token(tokens->data, path_list);
        tokens = tokens->next;
    }
    return (head);
}


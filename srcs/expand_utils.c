#include <debug.h>
#include <expand.h>
#include <libft.h>
#include <tokenize.h>

char	*search_env(const char *key, kvs *environ)
{
	int	i;

	i = 0;
	while (environ[i].key)
	{
		// null 文字まで比較させるための+1
		if (!ft_strncmp(environ[i].key, key, ft_strlen(environ[i].key) + 1))
            return (ft_strdup(environ[i].value));
		i++;
	}
	return (ft_strdup(""));
}

size_t	count_key_len(char *token, int t_index)
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

size_t	insert_env(char **buffer, char *token, kvs *environ)
{
	size_t	key_len;
	char	*value;
    char *substr;

	if (token[0] == '$')
		token++;
	key_len = count_key_len(token, 0);
    substr = ft_substr(token, 0, key_len);
	value = search_env(substr, environ);
    free(substr);
	*buffer = free_strjoin(*buffer, value);
	return (key_len);
}


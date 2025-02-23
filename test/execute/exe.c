#include <expand.h>
#include <invoke_commands.h>
#include <libft.h>
#include <tokenize.h>

static size_t	count_env(char **environ)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (environ[i])
	{
		count++;
		i++;
	}
	return (count);
}

static t_kvs	*create_env(char **environ)
{
	t_kvs		*env_list;
	char	**temp;
	int		i;
	size_t	count;

	count = count_env(environ);
	env_list = (t_kvs *)malloc(sizeof(t_kvs) * (count + 1));
	if (!env_list)
		return (NULL);
	ft_memset(env_list, 0, sizeof(t_kvs));
	i = 0;
	while (environ[i])
	{
		temp = ft_split(environ[i], '=');
		env_list[i].key = temp[0];
		env_list[i].value = temp[1];
		i++;
	}
	return (env_list);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	t_token		*tokens;
	t_token		*expanded_tokens;
	t_kvs			*env_list;

	env_list = create_env(environ);
	if (1 < argc)
	{
		tokens = tokenization(argv[1]);
		expanded_tokens = expand_tokens(&tokens, env_list);
		invoke_commands(expanded_tokens);
	}
}

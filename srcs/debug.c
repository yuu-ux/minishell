#include <invoke_commands.h>
#include <tokenize.h>

const char	*get_token_type_string(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return ("TOKEN_WORD");
	case TOKEN_EOF:
		return ("TOKEN_EOF");
	case TOKEN_UNKNOWN:
		return ("TOKEN_UNKNOWN");
	case TOKEN_PIPE:
		return ("TOKEN_PIPE");
	case TOKEN_REDIRECT_IN:
		return ("TOKEN_REDIRECT_IN");
	case TOKEN_REDIRECT_OUT:
		return ("TOKEN_REDIRECT_OUT");
	case TOKEN_REDIRECT_APPEND:
		return ("TOKEN_REDIRECT_APPEND");
	case TOKEN_REDIRECT_HEREDOC:
		return ("TOKEN_REDIRECT_HEREDOC");
	default:
		return ("UNKNOWN_TYPE");
	}
}

void	print_token(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("current->data->%s\n", current->data);
		current = current->next;
	}
}

void	print_node(t_node *head)
{
	t_node	*current;
	int		i;

	current = head;
	while (current)
	{
		printf("kind:%d\n", current->kind);
		if (current->argv != NULL)
		{
			i = 0;
			while (current->argv[i])
				printf("argv:%s\n", current->argv[i++]);
		}
		else
			printf("argv:(nil)\n");
		printf("---------------------------------\n");
		current = current->next;
	}
}

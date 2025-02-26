#include "tokenize.h"
#include <invoke_commands.h>

t_token_type	get_token_type(char *token)
{
	if (ft_strncmp(token, ">>", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(token, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else
		return (TOKEN_UNKNOWN);
}

bool	is_pipe(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (true);
	return (false);
}

bool	is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || \
		ft_strncmp(str, "<", 2) == 0 || \
		ft_strncmp(str, ">>", 3) == 0)
		return (true);
	return (false);
}
